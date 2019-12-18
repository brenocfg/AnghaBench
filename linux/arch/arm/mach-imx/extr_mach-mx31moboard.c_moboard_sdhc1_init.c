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
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  SDHC1_CD ; 
 int /*<<< orphan*/  SDHC1_WP ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,void*) ; 

__attribute__((used)) static int moboard_sdhc1_init(struct device *dev, irq_handler_t detect_irq,
		void *data)
{
	int ret;

	ret = gpio_request(SDHC1_CD, "sdhc-detect");
	if (ret)
		return ret;

	gpio_direction_input(SDHC1_CD);

	ret = gpio_request(SDHC1_WP, "sdhc-wp");
	if (ret)
		goto err_gpio_free;
	gpio_direction_input(SDHC1_WP);

	ret = request_irq(gpio_to_irq(SDHC1_CD), detect_irq,
		IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
		"sdhc1-card-detect", data);
	if (ret)
		goto err_gpio_free_2;

	return 0;

err_gpio_free_2:
	gpio_free(SDHC1_WP);
err_gpio_free:
	gpio_free(SDHC1_CD);

	return ret;
}