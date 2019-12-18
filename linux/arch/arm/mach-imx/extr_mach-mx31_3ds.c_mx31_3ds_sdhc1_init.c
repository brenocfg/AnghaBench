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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMUX_TO_GPIO (int /*<<< orphan*/ ) ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  MX31_PIN_GPIO3_1 ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_request_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx31_3ds_sdhc1_gpios ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,void*) ; 

__attribute__((used)) static int mx31_3ds_sdhc1_init(struct device *dev,
			       irq_handler_t detect_irq,
			       void *data)
{
	int ret;

	ret = gpio_request_array(mx31_3ds_sdhc1_gpios,
				 ARRAY_SIZE(mx31_3ds_sdhc1_gpios));
	if (ret) {
		pr_warn("Unable to request the SD/MMC GPIOs.\n");
		return ret;
	}

	ret = request_irq(gpio_to_irq(IOMUX_TO_GPIO(MX31_PIN_GPIO3_1)),
			  detect_irq,
			  IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
			  "sdhc1-detect", data);
	if (ret) {
		pr_warn("Unable to request the SD/MMC card-detect IRQ.\n");
		goto gpio_free;
	}

	return 0;

gpio_free:
	gpio_free_array(mx31_3ds_sdhc1_gpios,
			ARRAY_SIZE(mx31_3ds_sdhc1_gpios));
	return ret;
}