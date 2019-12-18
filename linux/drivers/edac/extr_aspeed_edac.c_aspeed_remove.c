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
struct mem_ctl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_MCR_INTR_CTRL ; 
 int /*<<< orphan*/  ASPEED_MCR_INTR_CTRL_ENABLE ; 
 int /*<<< orphan*/  aspeed_regmap ; 
 struct mem_ctl_info* edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_remove(struct platform_device *pdev)
{
	struct mem_ctl_info *mci;

	/* disable interrupts */
	regmap_update_bits(aspeed_regmap, ASPEED_MCR_INTR_CTRL,
			   ASPEED_MCR_INTR_CTRL_ENABLE, 0);

	/* free resources */
	mci = edac_mc_del_mc(&pdev->dev);
	if (mci)
		edac_mc_free(mci);

	return 0;
}