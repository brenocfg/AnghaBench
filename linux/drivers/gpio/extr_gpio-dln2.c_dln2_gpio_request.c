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
struct dln2_gpio_pin_val {scalar_t__ pin; int value; } ;
struct dln2_gpio_pin {scalar_t__ pin; } ;
struct dln2_gpio {int /*<<< orphan*/  output_enabled; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  rsp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
#define  DLN2_GPIO_DIRECTION_IN 129 
#define  DLN2_GPIO_DIRECTION_OUT 128 
 int /*<<< orphan*/  DLN2_GPIO_PIN_DISABLE ; 
 int /*<<< orphan*/  DLN2_GPIO_PIN_ENABLE ; 
 int /*<<< orphan*/  DLN2_GPIO_PIN_GET_DIRECTION ; 
 int EPROTO ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_le16 (unsigned int) ; 
 int dln2_gpio_pin_cmd (struct dln2_gpio*,int /*<<< orphan*/ ,unsigned int) ; 
 int dln2_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dln2_gpio_pin*,int,struct dln2_gpio_pin_val*,int*) ; 
 struct dln2_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct dln2_gpio *dln2 = gpiochip_get_data(chip);
	struct dln2_gpio_pin req = {
		.pin = cpu_to_le16(offset),
	};
	struct dln2_gpio_pin_val rsp;
	int len = sizeof(rsp);
	int ret;

	ret = dln2_gpio_pin_cmd(dln2, DLN2_GPIO_PIN_ENABLE, offset);
	if (ret < 0)
		return ret;

	/* cache the pin direction */
	ret = dln2_transfer(dln2->pdev, DLN2_GPIO_PIN_GET_DIRECTION,
			    &req, sizeof(req), &rsp, &len);
	if (ret < 0)
		return ret;
	if (len < sizeof(rsp) || req.pin != rsp.pin) {
		ret = -EPROTO;
		goto out_disable;
	}

	switch (rsp.value) {
	case DLN2_GPIO_DIRECTION_IN:
		clear_bit(offset, dln2->output_enabled);
		return 0;
	case DLN2_GPIO_DIRECTION_OUT:
		set_bit(offset, dln2->output_enabled);
		return 0;
	default:
		ret = -EPROTO;
		goto out_disable;
	}

out_disable:
	dln2_gpio_pin_cmd(dln2, DLN2_GPIO_PIN_DISABLE, offset);
	return ret;
}