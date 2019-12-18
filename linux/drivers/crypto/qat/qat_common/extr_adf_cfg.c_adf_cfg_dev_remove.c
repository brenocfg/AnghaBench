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
struct adf_cfg_device_data {int /*<<< orphan*/  debug; int /*<<< orphan*/  lock; int /*<<< orphan*/  sec_list; } ;
struct adf_accel_dev {struct adf_cfg_device_data* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  adf_cfg_section_del_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct adf_cfg_device_data*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void adf_cfg_dev_remove(struct adf_accel_dev *accel_dev)
{
	struct adf_cfg_device_data *dev_cfg_data = accel_dev->cfg;

	if (!dev_cfg_data)
		return;

	down_write(&dev_cfg_data->lock);
	adf_cfg_section_del_all(&dev_cfg_data->sec_list);
	up_write(&dev_cfg_data->lock);
	debugfs_remove(dev_cfg_data->debug);
	kfree(dev_cfg_data);
	accel_dev->cfg = NULL;
}