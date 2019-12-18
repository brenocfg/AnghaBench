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

/* Variables and functions */
#define  AR71XX_SOC_AR9341 132 
#define  AR71XX_SOC_AR9342 131 
#define  AR71XX_SOC_AR9344 130 
#define  AR71XX_SOC_QCA9533 129 
#define  AR71XX_SOC_QCA9533_V2 128 
 int ar71xx_soc ; 

__attribute__((used)) static int
ar71xx_gpio_oe_is_high(void)
{
	switch (ar71xx_soc) {
	case AR71XX_SOC_AR9341:
	case AR71XX_SOC_AR9342:
	case AR71XX_SOC_AR9344:
	case AR71XX_SOC_QCA9533:
	case AR71XX_SOC_QCA9533_V2:
		return 0;
	default:
		return 1;
	}
}