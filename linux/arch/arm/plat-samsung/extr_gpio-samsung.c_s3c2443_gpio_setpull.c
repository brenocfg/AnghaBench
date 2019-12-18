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
struct samsung_gpio_chip {int dummy; } ;
typedef  int samsung_gpio_pull_t ;

/* Variables and functions */
#define  S3C_GPIO_PULL_DOWN 130 
#define  S3C_GPIO_PULL_NONE 129 
#define  S3C_GPIO_PULL_UP 128 
 int samsung_gpio_setpull_updown (struct samsung_gpio_chip*,unsigned int,int) ; 

int s3c2443_gpio_setpull(struct samsung_gpio_chip *chip,
			 unsigned int off, samsung_gpio_pull_t pull)
{
	switch (pull) {
	case S3C_GPIO_PULL_NONE:
		pull = 0x01;
		break;
	case S3C_GPIO_PULL_UP:
		pull = 0x00;
		break;
	case S3C_GPIO_PULL_DOWN:
		pull = 0x02;
		break;
	}
	return samsung_gpio_setpull_updown(chip, off, pull);
}