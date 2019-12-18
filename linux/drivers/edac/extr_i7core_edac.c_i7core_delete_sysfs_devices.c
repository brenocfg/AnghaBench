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
struct mem_ctl_info {struct i7core_pvt* pvt_info; } ;
struct i7core_pvt {int /*<<< orphan*/  addrmatch_dev; int /*<<< orphan*/  chancounts_dev; int /*<<< orphan*/  is_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i7core_delete_sysfs_devices(struct mem_ctl_info *mci)
{
	struct i7core_pvt *pvt = mci->pvt_info;

	edac_dbg(1, "\n");

	if (!pvt->is_registered) {
		device_del(pvt->chancounts_dev);
		put_device(pvt->chancounts_dev);
	}
	device_del(pvt->addrmatch_dev);
	put_device(pvt->addrmatch_dev);
}