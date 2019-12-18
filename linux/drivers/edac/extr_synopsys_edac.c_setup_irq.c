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
struct synps_edac_priv {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {struct synps_edac_priv* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MC ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  enable_intr (struct synps_edac_priv*) ; 
 int /*<<< orphan*/  intr_handler ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_irq(struct mem_ctl_info *mci,
		     struct platform_device *pdev)
{
	struct synps_edac_priv *priv = mci->pvt_info;
	int ret, irq;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		edac_printk(KERN_ERR, EDAC_MC,
			    "No IRQ %d in DT\n", irq);
		return irq;
	}

	ret = devm_request_irq(&pdev->dev, irq, intr_handler,
			       0, dev_name(&pdev->dev), mci);
	if (ret < 0) {
		edac_printk(KERN_ERR, EDAC_MC, "Failed to request IRQ\n");
		return ret;
	}

	enable_intr(priv);

	return 0;
}