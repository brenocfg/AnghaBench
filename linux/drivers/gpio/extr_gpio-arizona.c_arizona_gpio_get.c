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
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int regcache_drop_region (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int arizona_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct arizona_gpio *arizona_gpio = gpiochip_get_data(chip);
	struct arizona *arizona = arizona_gpio->arizona;
	unsigned int reg, val;
	int ret;

	reg = ARIZONA_GPIO1_CTRL + offset;
	ret = regmap_read(arizona->regmap, reg, &val);
	if (ret < 0)
		return ret;

	/* Resume to read actual registers for input pins */
	if (val & ARIZONA_GPN_DIR) {
		ret = pm_runtime_get_sync(chip->parent);
		if (ret < 0) {
			dev_err(chip->parent, "Failed to resume: %d\n", ret);
			return ret;
		}

		/* Register is cached, drop it to ensure a physical read */
		ret = regcache_drop_region(arizona->regmap, reg, reg);
		if (ret < 0) {
			dev_err(chip->parent, "Failed to drop cache: %d\n",
				ret);
			return ret;
		}

		ret = regmap_read(arizona->regmap, reg, &val);
		if (ret < 0)
			return ret;

		pm_runtime_mark_last_busy(chip->parent);
		pm_runtime_put_autosuspend(chip->parent);
	}

	if (val & ARIZONA_GPN_LVL)
		return 1;
	else
		return 0;
}