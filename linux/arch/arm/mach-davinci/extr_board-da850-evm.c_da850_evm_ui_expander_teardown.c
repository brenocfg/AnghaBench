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
 unsigned int DA850_EVM_UI_EXP_SEL_A ; 
 unsigned int DA850_EVM_UI_EXP_SEL_B ; 
 unsigned int DA850_EVM_UI_EXP_SEL_C ; 
 int /*<<< orphan*/  da850_evm_ui_keys_device ; 
 int /*<<< orphan*/  gpio_free (unsigned int) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (unsigned int,int) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int da850_evm_ui_expander_teardown(struct i2c_client *client,
					unsigned gpio, unsigned ngpio, void *c)
{
	platform_device_unregister(&da850_evm_ui_keys_device);

	/* deselect all functionalities */
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_C, 1);
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_B, 1);
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_A, 1);

	gpio_free(gpio + DA850_EVM_UI_EXP_SEL_C);
	gpio_free(gpio + DA850_EVM_UI_EXP_SEL_B);
	gpio_free(gpio + DA850_EVM_UI_EXP_SEL_A);

	return 0;
}