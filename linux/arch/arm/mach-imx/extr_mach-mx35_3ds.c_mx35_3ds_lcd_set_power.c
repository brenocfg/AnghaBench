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
struct plat_lcd_data {int dummy; } ;
struct gpio_chip {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ENXIO ; 
 scalar_t__ GPIO_MC9S08DZ60_LCD_ENABLE ; 
 scalar_t__ gpio_is_valid (scalar_t__) ; 
 scalar_t__ gpio_request (scalar_t__,char*) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (scalar_t__,unsigned int) ; 
 struct gpio_chip* gpiochip_find (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lcd_power_gpio ; 
 int /*<<< orphan*/  mc9s08dz60_gpiochip_match ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void mx35_3ds_lcd_set_power(
				struct plat_lcd_data *pd, unsigned int power)
{
	struct gpio_chip *chip;

	if (!gpio_is_valid(lcd_power_gpio)) {
		chip = gpiochip_find(
				"mc9s08dz60", mc9s08dz60_gpiochip_match);
		if (chip) {
			lcd_power_gpio =
				chip->base + GPIO_MC9S08DZ60_LCD_ENABLE;
			if (gpio_request(lcd_power_gpio, "lcd_power") < 0) {
				pr_err("error: gpio already requested!\n");
				lcd_power_gpio = -ENXIO;
			}
		} else {
			pr_err("error: didn't find mc9s08dz60 gpio chip\n");
		}
	}

	if (gpio_is_valid(lcd_power_gpio))
		gpio_set_value_cansleep(lcd_power_gpio, power);
}