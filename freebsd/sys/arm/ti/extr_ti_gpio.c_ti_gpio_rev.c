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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AM335X_GPIO_REV ; 
#define  CHIP_AM335X 129 
#define  CHIP_OMAP_4 128 
 int /*<<< orphan*/  OMAP4_GPIO_REV ; 
 int ti_chip () ; 

__attribute__((used)) static uint32_t
ti_gpio_rev(void)
{
	switch(ti_chip()) {
#ifdef SOC_OMAP4
	case CHIP_OMAP_4:
		return (OMAP4_GPIO_REV);
#endif
#ifdef SOC_TI_AM335X
	case CHIP_AM335X:
		return (AM335X_GPIO_REV);
#endif
	}
	return (0);
}