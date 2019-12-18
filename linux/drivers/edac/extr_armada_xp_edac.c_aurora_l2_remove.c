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
struct edac_device_ctl_info {struct aurora_l2_drvdata* pvt_info; } ;
struct aurora_l2_drvdata {int /*<<< orphan*/  debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_del_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_device_free_ctl_info (struct edac_device_ctl_info*) ; 
 struct edac_device_ctl_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aurora_l2_remove(struct platform_device *pdev)
{
	struct edac_device_ctl_info *dci = platform_get_drvdata(pdev);
#ifdef CONFIG_EDAC_DEBUG
	struct aurora_l2_drvdata *drvdata = dci->pvt_info;

	edac_debugfs_remove_recursive(drvdata->debugfs);
#endif
	edac_device_del_device(&pdev->dev);
	edac_device_free_ctl_info(dci);
	platform_set_drvdata(pdev, NULL);

	return 0;
}