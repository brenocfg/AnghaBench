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
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct bd70528_gpio {TYPE_1__ chip; } ;

/* Variables and functions */
 int bd70528_get_direction (struct gpio_chip*,unsigned int) ; 
 int bd70528_gpio_get_i (struct bd70528_gpio*,unsigned int) ; 
 int bd70528_gpio_get_o (struct bd70528_gpio*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct bd70528_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int bd70528_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	int ret;
	struct bd70528_gpio *bdgpio = gpiochip_get_data(chip);

	/*
	 * There is a race condition where someone might be changing the
	 * GPIO direction after we get it but before we read the value. But
	 * application design where GPIO direction may be changed just when
	 * we read GPIO value would be pointless as reader could not know
	 * whether the returned high/low state is caused by input or output.
	 * Or then there must be other ways to mitigate the issue. Thus
	 * locking would make no sense.
	 */
	ret = bd70528_get_direction(chip, offset);
	if (ret == 0)
		ret = bd70528_gpio_get_o(bdgpio, offset);
	else if (ret == 1)
		ret = bd70528_gpio_get_i(bdgpio, offset);
	else
		dev_err(bdgpio->chip.dev, "failed to read GPIO direction\n");

	return ret;
}