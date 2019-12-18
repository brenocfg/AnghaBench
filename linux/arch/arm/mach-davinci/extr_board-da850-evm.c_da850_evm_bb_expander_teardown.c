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
 int /*<<< orphan*/  da850_evm_bb_leds_device ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int da850_evm_bb_expander_teardown(struct i2c_client *client,
					unsigned gpio, unsigned ngpio, void *c)
{
	platform_device_unregister(&da850_evm_bb_leds_device);
	platform_device_unregister(&da850_evm_bb_keys_device);

	return 0;
}