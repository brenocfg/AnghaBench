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
struct hb_l2_drvdata {int sb_irq; int db_irq; scalar_t__ base; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  ctl_name; struct hb_l2_drvdata* pvt_info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SR_CLR_DB_ECC_INTR ; 
 scalar_t__ SR_CLR_SB_ECC_INTR ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t highbank_l2_err_handler(int irq, void *dev_id)
{
	struct edac_device_ctl_info *dci = dev_id;
	struct hb_l2_drvdata *drvdata = dci->pvt_info;

	if (irq == drvdata->sb_irq) {
		writel(1, drvdata->base + SR_CLR_SB_ECC_INTR);
		edac_device_handle_ce(dci, 0, 0, dci->ctl_name);
	}
	if (irq == drvdata->db_irq) {
		writel(1, drvdata->base + SR_CLR_DB_ECC_INTR);
		edac_device_handle_ue(dci, 0, 0, dci->ctl_name);
	}

	return IRQ_HANDLED;
}