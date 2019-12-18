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
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct arizona_gpio {struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ARIZONA_GPIO1_CTRL ; 
 int /*<<< orphan*/  ARIZONA_GPN_DIR ; 
 struct arizona_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int gpiochip_line_is_persistent (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int regmap_update_bits_check (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int arizona_gpio_direction_in(struct gpio_chip *chip, unsigned offset)
{
	struct arizona_gpio *arizona_gpio = gpiochip_get_data(chip);
	struct arizona *arizona = arizona_gpio->arizona;
	bool persistent = gpiochip_line_is_persistent(chip, offset);
	bool change;
	int ret;

	ret = regmap_update_bits_check(arizona->regmap,
				       ARIZONA_GPIO1_CTRL + offset,
				       ARIZONA_GPN_DIR, ARIZONA_GPN_DIR,
				       &change);
	if (ret < 0)
		return ret;

	if (change && persistent) {
		pm_runtime_mark_last_busy(chip->parent);
		pm_runtime_put_autosuspend(chip->parent);
	}

	return 0;
}