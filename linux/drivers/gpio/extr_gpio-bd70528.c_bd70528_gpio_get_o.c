#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct bd70528_gpio {TYPE_1__ chip; } ;

/* Variables and functions */
 unsigned int BD70528_GPIO_OUT_MASK ; 
 int /*<<< orphan*/  GPIO_OUT_REG (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int bd70528_gpio_get_o(struct bd70528_gpio *bdgpio, unsigned int offset)
{
	int ret;
	unsigned int val;

	ret = regmap_read(bdgpio->chip.regmap, GPIO_OUT_REG(offset), &val);
	if (!ret)
		ret = !!(val & BD70528_GPIO_OUT_MASK);
	else
		dev_err(bdgpio->chip.dev, "GPIO (out) state read failed\n");

	return ret;
}