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
 int /*<<< orphan*/  cpc925_del_edac_devices () ; 
 int /*<<< orphan*/  cpc925_mc_exit (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 struct mem_ctl_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cpc925_remove(struct platform_device *pdev)
{
	struct mem_ctl_info *mci = platform_get_drvdata(pdev);

	/*
	 * Delete common edac devices before edac mc, because
	 * the former share the MMIO of the latter.
	 */
	cpc925_del_edac_devices();
	cpc925_mc_exit(mci);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_free(mci);

	return 0;
}