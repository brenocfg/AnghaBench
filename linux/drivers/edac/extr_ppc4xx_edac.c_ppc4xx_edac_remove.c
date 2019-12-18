#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ded; int /*<<< orphan*/  sec; } ;
struct ppc4xx_edac_pdata {int /*<<< orphan*/  dcr_host; TYPE_1__ irqs; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {int /*<<< orphan*/  pdev; struct ppc4xx_edac_pdata* pvt_info; } ;

/* Variables and functions */
 scalar_t__ EDAC_OPSTATE_INT ; 
 int /*<<< orphan*/  SDRAM_DCR_RESOURCE_LEN ; 
 int /*<<< orphan*/  dcr_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mem_ctl_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 scalar_t__ edac_op_state ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mem_ctl_info*) ; 

__attribute__((used)) static int
ppc4xx_edac_remove(struct platform_device *op)
{
	struct mem_ctl_info *mci = dev_get_drvdata(&op->dev);
	struct ppc4xx_edac_pdata *pdata = mci->pvt_info;

	if (edac_op_state == EDAC_OPSTATE_INT) {
		free_irq(pdata->irqs.sec, mci);
		free_irq(pdata->irqs.ded, mci);
	}

	dcr_unmap(pdata->dcr_host, SDRAM_DCR_RESOURCE_LEN);

	edac_mc_del_mc(mci->pdev);
	edac_mc_free(mci);

	return 0;
}