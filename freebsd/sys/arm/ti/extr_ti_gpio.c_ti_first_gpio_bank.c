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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  AM335X_FIRST_GPIO_BANK ; 
#define  CHIP_AM335X 129 
#define  CHIP_OMAP_4 128 
 int /*<<< orphan*/  OMAP4_FIRST_GPIO_BANK ; 
 int ti_chip () ; 

__attribute__((used)) static u_int
ti_first_gpio_bank(void)
{
	switch(ti_chip()) {
#ifdef SOC_OMAP4
	case CHIP_OMAP_4:
		return (OMAP4_FIRST_GPIO_BANK);
#endif
#ifdef SOC_TI_AM335X
	case CHIP_AM335X:
		return (AM335X_FIRST_GPIO_BANK);
#endif
	}
	return (0);
}