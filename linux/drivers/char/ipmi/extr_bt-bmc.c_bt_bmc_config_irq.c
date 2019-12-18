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
struct platform_device {struct device dev; } ;
struct bt_bmc {scalar_t__ offset; int /*<<< orphan*/  map; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ BT_CR1 ; 
 int BT_CR1_IRQ_H2B ; 
 int BT_CR1_IRQ_HBUSY ; 
 int /*<<< orphan*/  DEVICE_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  bt_bmc_irq ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bt_bmc*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int bt_bmc_config_irq(struct bt_bmc *bt_bmc,
			     struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int rc;

	bt_bmc->irq = platform_get_irq(pdev, 0);
	if (!bt_bmc->irq)
		return -ENODEV;

	rc = devm_request_irq(dev, bt_bmc->irq, bt_bmc_irq, IRQF_SHARED,
			      DEVICE_NAME, bt_bmc);
	if (rc < 0) {
		dev_warn(dev, "Unable to request IRQ %d\n", bt_bmc->irq);
		bt_bmc->irq = 0;
		return rc;
	}

	/*
	 * Configure IRQs on the bmc clearing the H2B and HBUSY bits;
	 * H2B will be asserted when the bmc has data for us; HBUSY
	 * will be cleared (along with B2H) when we can write the next
	 * message to the BT buffer
	 */
	rc = regmap_update_bits(bt_bmc->map, bt_bmc->offset + BT_CR1,
				(BT_CR1_IRQ_H2B | BT_CR1_IRQ_HBUSY),
				(BT_CR1_IRQ_H2B | BT_CR1_IRQ_HBUSY));

	return rc;
}