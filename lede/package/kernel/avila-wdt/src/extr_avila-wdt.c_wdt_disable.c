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
 int* IXP4XX_GPIO_GPCLKR ; 

__attribute__((used)) static void wdt_disable(void)
{
	/* Re-enable clock generator output on GPIO 14/15 */
	*IXP4XX_GPIO_GPCLKR |= (1 << 8);
}