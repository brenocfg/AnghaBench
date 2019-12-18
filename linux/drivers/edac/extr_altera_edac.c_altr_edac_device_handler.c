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
struct edac_device_prv_data {scalar_t__ ue_clear_mask; scalar_t__ ce_clear_mask; } ;
struct edac_device_ctl_info {struct altr_edac_device_dev* pvt_info; } ;
struct altr_edac_device_dev {int sb_irq; int db_irq; int /*<<< orphan*/  edac_dev_name; int /*<<< orphan*/  base; struct edac_device_prv_data* data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t altr_edac_device_handler(int irq, void *dev_id)
{
	irqreturn_t ret_value = IRQ_NONE;
	struct edac_device_ctl_info *dci = dev_id;
	struct altr_edac_device_dev *drvdata = dci->pvt_info;
	const struct edac_device_prv_data *priv = drvdata->data;

	if (irq == drvdata->sb_irq) {
		if (priv->ce_clear_mask)
			writel(priv->ce_clear_mask, drvdata->base);
		edac_device_handle_ce(dci, 0, 0, drvdata->edac_dev_name);
		ret_value = IRQ_HANDLED;
	} else if (irq == drvdata->db_irq) {
		if (priv->ue_clear_mask)
			writel(priv->ue_clear_mask, drvdata->base);
		edac_device_handle_ue(dci, 0, 0, drvdata->edac_dev_name);
		panic("\nEDAC:ECC_DEVICE[Uncorrectable errors]\n");
		ret_value = IRQ_HANDLED;
	} else {
		WARN_ON(1);
	}

	return ret_value;
}