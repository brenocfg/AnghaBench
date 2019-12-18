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
 int /*<<< orphan*/  S3C2410_GPJ (int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rx1950_bat_init(void)
{
	int ret;

	ret = gpio_request(S3C2410_GPJ(2), "rx1950-charger-enable-1");
	if (ret)
		goto err_gpio1;
	ret = gpio_request(S3C2410_GPJ(3), "rx1950-charger-enable-2");
	if (ret)
		goto err_gpio2;

	return 0;

err_gpio2:
	gpio_free(S3C2410_GPJ(2));
err_gpio1:
	return ret;
}