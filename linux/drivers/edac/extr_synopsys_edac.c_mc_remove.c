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
struct synps_edac_priv {TYPE_1__* p_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {struct synps_edac_priv* pvt_info; } ;
struct TYPE_2__ {int quirks; } ;

/* Variables and functions */
 int DDR_ECC_DATA_POISON_SUPPORT ; 
 int DDR_ECC_INTR_SUPPORT ; 
 int /*<<< orphan*/  disable_intr (struct synps_edac_priv*) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_remove_sysfs_attributes (struct mem_ctl_info*) ; 
 struct mem_ctl_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mc_remove(struct platform_device *pdev)
{
	struct mem_ctl_info *mci = platform_get_drvdata(pdev);
	struct synps_edac_priv *priv = mci->pvt_info;

	if (priv->p_data->quirks & DDR_ECC_INTR_SUPPORT)
		disable_intr(priv);

#ifdef CONFIG_EDAC_DEBUG
	if (priv->p_data->quirks & DDR_ECC_DATA_POISON_SUPPORT)
		edac_remove_sysfs_attributes(mci);
#endif

	edac_mc_del_mc(&pdev->dev);
	edac_mc_free(mci);

	return 0;
}