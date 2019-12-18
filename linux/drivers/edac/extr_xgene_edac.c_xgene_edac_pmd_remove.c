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
struct xgene_edac_pmd_ctx {struct edac_device_ctl_info* edac_dev; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_device_del_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_free_ctl_info (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  xgene_edac_pmd_hw_ctl (struct edac_device_ctl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_edac_pmd_remove(struct xgene_edac_pmd_ctx *pmd)
{
	struct edac_device_ctl_info *edac_dev = pmd->edac_dev;

	xgene_edac_pmd_hw_ctl(edac_dev, 0);
	edac_device_del_device(edac_dev->dev);
	edac_device_free_ctl_info(edac_dev);
	return 0;
}