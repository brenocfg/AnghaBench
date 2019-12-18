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
struct s3c2410_hcd_info {int dummy; } ;

/* Variables and functions */
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  S3C64XX_GPL (int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct s3c2410_hcd_info*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_smartq5 () ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct s3c2410_hcd_info*) ; 
 int /*<<< orphan*/  smartq_usb_host_ocirq ; 

__attribute__((used)) static void smartq_usb_host_enableoc(struct s3c2410_hcd_info *info, int on)
{
	int ret;

	/* This isn't present on a SmartQ 5 board */
	if (machine_is_smartq5())
		return;

	if (on) {
		ret = request_irq(gpio_to_irq(S3C64XX_GPL(10)),
				  smartq_usb_host_ocirq,
				  IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				  "USB host overcurrent", info);
		if (ret != 0)
			pr_err("failed to request usb oc irq: %d\n", ret);
	} else {
		free_irq(gpio_to_irq(S3C64XX_GPL(10)), info);
	}
}