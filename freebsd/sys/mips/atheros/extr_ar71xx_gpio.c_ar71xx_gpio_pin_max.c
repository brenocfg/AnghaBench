#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_GPIO_PINS ; 
#define  AR71XX_SOC_AR7240 141 
#define  AR71XX_SOC_AR7241 140 
#define  AR71XX_SOC_AR7242 139 
#define  AR71XX_SOC_AR9130 138 
#define  AR71XX_SOC_AR9132 137 
#define  AR71XX_SOC_AR9330 136 
#define  AR71XX_SOC_AR9331 135 
#define  AR71XX_SOC_AR9341 134 
#define  AR71XX_SOC_AR9342 133 
#define  AR71XX_SOC_AR9344 132 
#define  AR71XX_SOC_QCA9533 131 
#define  AR71XX_SOC_QCA9533_V2 130 
#define  AR71XX_SOC_QCA9556 129 
#define  AR71XX_SOC_QCA9558 128 
 int /*<<< orphan*/  AR7241_GPIO_PINS ; 
 int /*<<< orphan*/  AR724X_GPIO_PINS ; 
 int /*<<< orphan*/  AR91XX_GPIO_PINS ; 
 int /*<<< orphan*/  AR933X_GPIO_COUNT ; 
 int /*<<< orphan*/  AR934X_GPIO_COUNT ; 
 int /*<<< orphan*/  QCA953X_GPIO_COUNT ; 
 int /*<<< orphan*/  QCA955X_GPIO_COUNT ; 
 int ar71xx_soc ; 

__attribute__((used)) static int
ar71xx_gpio_pin_max(device_t dev, int *maxpin)
{

	switch (ar71xx_soc) {
		case AR71XX_SOC_AR9130:
		case AR71XX_SOC_AR9132:
			*maxpin = AR91XX_GPIO_PINS - 1;
			break;
		case AR71XX_SOC_AR7240:
		case AR71XX_SOC_AR7242:
			*maxpin = AR724X_GPIO_PINS - 1;
			break;
		case AR71XX_SOC_AR7241:
			*maxpin = AR7241_GPIO_PINS - 1;
			break;
		case AR71XX_SOC_AR9330:
		case AR71XX_SOC_AR9331:
			*maxpin = AR933X_GPIO_COUNT - 1;
			break;
		case AR71XX_SOC_AR9341:
		case AR71XX_SOC_AR9342:
		case AR71XX_SOC_AR9344:
			*maxpin = AR934X_GPIO_COUNT - 1;
			break;
		case AR71XX_SOC_QCA9533:
		case AR71XX_SOC_QCA9533_V2:
			*maxpin = QCA953X_GPIO_COUNT - 1;
			break;
		case AR71XX_SOC_QCA9556:
		case AR71XX_SOC_QCA9558:
			*maxpin = QCA955X_GPIO_COUNT - 1;
			break;
		default:
			*maxpin = AR71XX_GPIO_PINS - 1;
	}
	return (0);
}