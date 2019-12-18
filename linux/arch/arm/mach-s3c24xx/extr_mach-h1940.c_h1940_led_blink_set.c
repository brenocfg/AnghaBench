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
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GPIO_LED_BLINK 132 
#define  GPIO_LED_NO_BLINK_HIGH 131 
#define  GPIO_LED_NO_BLINK_LOW 130 
 int H1940_LATCH_LED_FLASH ; 
#define  H1940_LATCH_LED_GREEN 129 
#define  H1940_LATCH_LED_RED 128 
 int S3C2410_GPA (int) ; 
 int desc_to_gpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpio_get_value (int) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int /*<<< orphan*/  h1940_blink_spin ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int h1940_led_blink_set(struct gpio_desc *desc, int state,
	unsigned long *delay_on, unsigned long *delay_off)
{
	int blink_gpio, check_gpio1, check_gpio2;
	int gpio = desc ? desc_to_gpio(desc) : -EINVAL;

	switch (gpio) {
	case H1940_LATCH_LED_GREEN:
		blink_gpio = S3C2410_GPA(7);
		check_gpio1 = S3C2410_GPA(1);
		check_gpio2 = S3C2410_GPA(3);
		break;
	case H1940_LATCH_LED_RED:
		blink_gpio = S3C2410_GPA(1);
		check_gpio1 = S3C2410_GPA(7);
		check_gpio2 = S3C2410_GPA(3);
		break;
	default:
		blink_gpio = S3C2410_GPA(3);
		check_gpio1 = S3C2410_GPA(1);
		check_gpio2 = S3C2410_GPA(7);
		break;
	}

	if (delay_on && delay_off && !*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	spin_lock(&h1940_blink_spin);

	switch (state) {
	case GPIO_LED_NO_BLINK_LOW:
	case GPIO_LED_NO_BLINK_HIGH:
		if (!gpio_get_value(check_gpio1) &&
		    !gpio_get_value(check_gpio2))
			gpio_set_value(H1940_LATCH_LED_FLASH, 0);
		gpio_set_value(blink_gpio, 0);
		if (gpio_is_valid(gpio))
			gpio_set_value(gpio, state);
		break;
	case GPIO_LED_BLINK:
		if (gpio_is_valid(gpio))
			gpio_set_value(gpio, 0);
		gpio_set_value(H1940_LATCH_LED_FLASH, 1);
		gpio_set_value(blink_gpio, 1);
		break;
	}

	spin_unlock(&h1940_blink_spin);

	return 0;
}