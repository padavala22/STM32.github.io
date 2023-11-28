/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "SM_test.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <string.h>
#include "ssd1306.h"
#include "ssd1306_tests.h"
//UART_HandleTypeDef huart2;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
enum statetype {
	              state_A = 0,
				  state_B,
				  state_C,
				  state_D
};
typedef enum statetype state;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t test1;
state present_state;

void fun_state_a(void){
	 ssd1306_Fill(Black);
	sm_test1("123456789" , 15);
	sm_test1("123456789" , 25);
	sm_test1("123456789" , 35);
	sm_test1("123456789" , 45);
	 HAL_UART_Transmit(&huart2, (uint8_t *)"hello state_a\r\n", strlen("hello state_d\r\n"), HAL_MAX_DELAY);
}
void fun_state_b(void){
	 ssd1306_Fill(Black);
	sm_test1("ABCDEFGHIJKL" , 15);
	sm_test1("ABCDEFGHIJKL" , 25);
	sm_test1("ABCDEFGHIJKL" , 35);
	sm_test1("ABCDEFGHIJKL" , 45);
	 HAL_UART_Transmit(&huart2, (uint8_t *)"hello state_b\r\n", strlen("hello state_d\r\n"), HAL_MAX_DELAY);
}
void fun_state_c(void){
	 ssd1306_Fill(Black);
	sm_test1("!@#$%^&*(" , 15);
	sm_test1("!@#$%^&*(" , 25);
	sm_test1("!@#$%^&*(" , 35);
	sm_test1("!@#$%^&*(" , 45);
	 HAL_UART_Transmit(&huart2, (uint8_t *)"hello state_c\r\n", strlen("hello state_d\r\n"), HAL_MAX_DELAY);
}
void fun_state_d(void){
	 ssd1306_Fill(Black);
	sm_test1("fffffffffffffff" , 15);
	sm_test1("fffffffffffffff" , 25);
	sm_test1("fffffffffffffff" , 35);
	sm_test1("fffffffffffffff" , 45);
	 HAL_UART_Transmit(&huart2, (uint8_t *)"hello state_d\r\n", strlen("hello state_d\r\n"), HAL_MAX_DELAY);
}
void (*ptr[])(void)={fun_state_a,fun_state_b,fun_state_c,fun_state_d};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  //uint8_t test;
  //printf("hello SM");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//char txData[] = "Hello, UART!\r\n";
  ssd1306_Init();
  ssd1306_Fill(White);
  ssd1306_UpdateScreen();
  while (1)
  {
	  //ssd1306_TestAll();
	 // HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState)(LD2_GPIO_Port, &GPIO_InitStruct);
	 /* if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) {
	      // Input is high
		  ;
	  } else {
	      // Input is low
		  HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin );
	  }*/

   // HAL_UART_Transmit(&huart2, (uint8_t *)txData, strlen(txData), HAL_MAX_DELAY);
    HAL_Delay(1000);
    ptr[present_state]();
    if (present_state == state_D)
    	present_state=state_A;
    else
    	present_state++;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 7;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
