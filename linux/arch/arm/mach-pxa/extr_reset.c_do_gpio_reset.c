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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  do_hw_reset () ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int reset_gpio ; 

__attribute__((used)) static void do_gpio_reset(void)
{
	BUG_ON(reset_gpio == -1);

	/* drive it low */
	gpio_direction_output(reset_gpio, 0);
	mdelay(2);
	/* rising edge or drive high */
	gpio_set_value(reset_gpio, 1);
	mdelay(2);
	/* falling edge */
	gpio_set_value(reset_gpio, 0);

	/* give it some time */
	mdelay(10);

	WARN_ON(1);
	/* fallback */
	do_hw_reset();
}