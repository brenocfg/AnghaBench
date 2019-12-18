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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  da850_evm_bb_keys_device ; 
 int /*<<< orphan*/  da850_evm_bb_keys_init (unsigned int) ; 
 int /*<<< orphan*/  da850_evm_bb_leds_device ; 
 int /*<<< orphan*/  da850_evm_bb_leds_gpio_table ; 
 int /*<<< orphan*/  gpiod_add_lookup_table (int /*<<< orphan*/ *) ; 
 int platform_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int da850_evm_bb_expander_setup(struct i2c_client *client,
						unsigned gpio, unsigned ngpio,
						void *c)
{
	int ret;

	/*
	 * Register the switches and pushbutton on the baseboard as a gpio-keys
	 * device.
	 */
	da850_evm_bb_keys_init(gpio);
	ret = platform_device_register(&da850_evm_bb_keys_device);
	if (ret) {
		pr_warn("Could not register baseboard GPIO expander keys");
		goto io_exp_setup_sw_fail;
	}

	gpiod_add_lookup_table(&da850_evm_bb_leds_gpio_table);
	ret = platform_device_register(&da850_evm_bb_leds_device);
	if (ret) {
		pr_warn("Could not register baseboard GPIO expander LEDs");
		goto io_exp_setup_leds_fail;
	}

	return 0;

io_exp_setup_leds_fail:
	platform_device_unregister(&da850_evm_bb_keys_device);
io_exp_setup_sw_fail:
	return ret;
}