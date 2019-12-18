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
struct cpc925_dev_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  (* exit ) (struct cpc925_dev_info*) ;int /*<<< orphan*/  pdev; TYPE_1__* edac_dev; scalar_t__ init; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct cpc925_dev_info* cpc925_devs ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_del_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_free_ctl_info (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cpc925_dev_info*) ; 

__attribute__((used)) static void cpc925_del_edac_devices(void)
{
	struct cpc925_dev_info *dev_info;

	for (dev_info = &cpc925_devs[0]; dev_info->init; dev_info++) {
		if (dev_info->edac_dev) {
			edac_device_del_device(dev_info->edac_dev->dev);
			edac_device_free_ctl_info(dev_info->edac_dev);
			platform_device_unregister(dev_info->pdev);
		}

		if (dev_info->exit)
			dev_info->exit(dev_info);

		edac_dbg(0, "Successfully deleted edac device for %s\n",
			 dev_info->ctl_name);
	}
}