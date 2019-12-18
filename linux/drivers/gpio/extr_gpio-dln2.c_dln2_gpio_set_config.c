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
struct gpio_chip {int dummy; } ;
struct dln2_gpio {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  duration ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_GPIO_SET_DEBOUNCE ; 
 int ENOTSUPP ; 
 scalar_t__ PIN_CONFIG_INPUT_DEBOUNCE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int dln2_transfer_tx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct dln2_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 scalar_t__ pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int dln2_gpio_set_config(struct gpio_chip *chip, unsigned offset,
				unsigned long config)
{
	struct dln2_gpio *dln2 = gpiochip_get_data(chip);
	__le32 duration;

	if (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		return -ENOTSUPP;

	duration = cpu_to_le32(pinconf_to_config_argument(config));
	return dln2_transfer_tx(dln2->pdev, DLN2_GPIO_SET_DEBOUNCE,
				&duration, sizeof(duration));
}