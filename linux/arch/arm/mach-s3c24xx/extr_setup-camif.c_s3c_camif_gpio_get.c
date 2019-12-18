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

/* Variables and functions */
 int S3C_CAMIF_NUM_GPIOS ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  camif_get_gpios (int*,int*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int s3c_gpio_cfgpin (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_setpull (int,int /*<<< orphan*/ ) ; 

int s3c_camif_gpio_get(void)
{
	int gpio_start, gpio_reset;
	int ret, i;

	camif_get_gpios(&gpio_start, &gpio_reset);

	for (i = 0; i < S3C_CAMIF_NUM_GPIOS; i++) {
		int gpio = gpio_start + i;

		if (gpio == gpio_reset)
			continue;

		ret = gpio_request(gpio, "camif");
		if (!ret)
			ret = s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		if (ret) {
			pr_err("failed to configure GPIO %d\n", gpio);
			for (--i; i >= 0; i--)
				gpio_free(gpio--);
			return ret;
		}
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	return 0;
}