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
 unsigned int ARIZONA_GPN_DIR ; 
 unsigned int ARIZONA_GPN_LVL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct arizona_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int gpiochip_line_is_persistent (struct gpio_chip*,unsigned int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int arizona_gpio_direction_out(struct gpio_chip *chip,
				     unsigned offset, int value)
{
	struct arizona_gpio *arizona_gpio = gpiochip_get_data(chip);
	struct arizona *arizona = arizona_gpio->arizona;
	bool persistent = gpiochip_line_is_persistent(chip, offset);
	unsigned int val;
	int ret;

	ret = regmap_read(arizona->regmap, ARIZONA_GPIO1_CTRL + offset, &val);
	if (ret < 0)
		return ret;

	if ((val & ARIZONA_GPN_DIR) && persistent) {
		ret = pm_runtime_get_sync(chip->parent);
		if (ret < 0) {
			dev_err(chip->parent, "Failed to resume: %d\n", ret);
			return ret;
		}
	}

	if (value)
		value = ARIZONA_GPN_LVL;

	return regmap_update_bits(arizona->regmap, ARIZONA_GPIO1_CTRL + offset,
				  ARIZONA_GPN_DIR | ARIZONA_GPN_LVL, value);
}