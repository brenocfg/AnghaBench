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
struct spi_device {int dummy; } ;
struct gen_74x164_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio_chip; int /*<<< orphan*/  gpiod_oe; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct gen_74x164_chip* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int gen_74x164_remove(struct spi_device *spi)
{
	struct gen_74x164_chip *chip = spi_get_drvdata(spi);

	gpiod_set_value_cansleep(chip->gpiod_oe, 0);
	gpiochip_remove(&chip->gpio_chip);
	mutex_destroy(&chip->lock);

	return 0;
}