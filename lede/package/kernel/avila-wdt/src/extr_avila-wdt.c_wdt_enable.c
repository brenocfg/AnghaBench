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
 int /*<<< orphan*/  IXP4XX_GPIO_LOW ; 
 int /*<<< orphan*/  IXP4XX_GPIO_OUT ; 
 int /*<<< orphan*/  WDT_RUNNING ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpio_line_config (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_line_set (int,int /*<<< orphan*/ ) ; 
 int heartbeat ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_counter ; 
 int /*<<< orphan*/  wdt_refresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static void wdt_enable(void)
{
	atomic_set(&wdt_counter, heartbeat * 2);

	/* Disable clock generator output on GPIO 14/15 */
	*IXP4XX_GPIO_GPCLKR &= ~(1 << 8);

	/* activate GPIO 14 out */
	gpio_line_config(14, IXP4XX_GPIO_OUT);
	gpio_line_set(14, IXP4XX_GPIO_LOW);

	if (!test_bit(WDT_RUNNING, &wdt_status))
		wdt_refresh(0);
	set_bit(WDT_RUNNING, &wdt_status);
}