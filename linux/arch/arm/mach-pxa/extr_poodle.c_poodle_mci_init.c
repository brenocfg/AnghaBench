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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  POODLE_GPIO_SD_PWR ; 
 int /*<<< orphan*/  POODLE_GPIO_SD_PWR1 ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int poodle_mci_init(struct device *dev, irq_handler_t poodle_detect_int, void *data)
{
	int err;

	err = gpio_request(POODLE_GPIO_SD_PWR, "SD_PWR");
	if (err)
		goto err_free_2;

	err = gpio_request(POODLE_GPIO_SD_PWR1, "SD_PWR1");
	if (err)
		goto err_free_3;

	gpio_direction_output(POODLE_GPIO_SD_PWR, 0);
	gpio_direction_output(POODLE_GPIO_SD_PWR1, 0);

	return 0;

err_free_3:
	gpio_free(POODLE_GPIO_SD_PWR);
err_free_2:
	return err;
}