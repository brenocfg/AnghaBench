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
struct bcm_kona_gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_kona_gpio_unlock_gpio (struct bcm_kona_gpio*,unsigned int) ; 
 struct bcm_kona_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int bcm_kona_gpio_request(struct gpio_chip *chip, unsigned gpio)
{
	struct bcm_kona_gpio *kona_gpio = gpiochip_get_data(chip);

	bcm_kona_gpio_unlock_gpio(kona_gpio, gpio);
	return 0;
}