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
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  gpio_request_one (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int /*<<< orphan*/  gpio_wdt_timer ; 
 int /*<<< orphan*/  gpio_wdt_toggle (int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int),int) ; 

__attribute__((used)) static void init_sbr_ac1750_wdt(int gpio_wdt){
	
	if (gpio_wdt >= 0) {
		gpio_request_one(gpio_wdt, GPIOF_OUT_INIT_HIGH, "watchdog");
		gpio_set_value(gpio_wdt, 0);
		ndelay(1000);
		gpio_set_value(gpio_wdt, 1);
		setup_timer(&gpio_wdt_timer, gpio_wdt_toggle, gpio_wdt);
		gpio_wdt_toggle(gpio_wdt);
	}
}