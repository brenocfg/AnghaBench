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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_MCR_INTR_CTRL ; 
 int /*<<< orphan*/  ASPEED_MCR_INTR_CTRL_ENABLE ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  aspeed_regmap ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mcr_isr ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_irq(void *ctx, struct platform_device *pdev)
{
	int irq;
	int rc;

	/* register interrupt handler */
	irq = platform_get_irq(pdev, 0);
	dev_dbg(&pdev->dev, "got irq %d\n", irq);
	if (!irq)
		return -ENODEV;

	rc = devm_request_irq(&pdev->dev, irq, mcr_isr, IRQF_TRIGGER_HIGH,
			      DRV_NAME, ctx);
	if (rc) {
		dev_err(&pdev->dev, "unable to request irq %d\n", irq);
		return rc;
	}

	/* enable interrupts */
	regmap_update_bits(aspeed_regmap, ASPEED_MCR_INTR_CTRL,
			   ASPEED_MCR_INTR_CTRL_ENABLE,
			   ASPEED_MCR_INTR_CTRL_ENABLE);

	return 0;
}