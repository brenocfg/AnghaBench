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
 int /*<<< orphan*/  SBR_AC1750_EXT_WDT_TIMEOUT_MS ; 
 int /*<<< orphan*/  gpio_set_value (unsigned long,int) ; 
 int /*<<< orphan*/  gpio_wdt_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_wdt_toggle(unsigned long gpio)
{
	static int state;

	state = !state;
	gpio_set_value(gpio, state);

	mod_timer(&gpio_wdt_timer,
		  jiffies + msecs_to_jiffies(SBR_AC1750_EXT_WDT_TIMEOUT_MS));
}