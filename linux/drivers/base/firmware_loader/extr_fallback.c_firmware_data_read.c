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
struct kobject {int dummy; } ;
struct fw_sysfs {struct fw_priv* fw_priv; } ;
struct fw_priv {scalar_t__ size; scalar_t__ data; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 size_t ENODEV ; 
 int /*<<< orphan*/  firmware_rw (struct fw_priv*,char*,scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  firmware_rw_data (struct fw_priv*,char*,scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  fw_lock ; 
 scalar_t__ fw_sysfs_done (struct fw_priv*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fw_sysfs* to_fw_sysfs (struct device*) ; 

__attribute__((used)) static ssize_t firmware_data_read(struct file *filp, struct kobject *kobj,
				  struct bin_attribute *bin_attr,
				  char *buffer, loff_t offset, size_t count)
{
	struct device *dev = kobj_to_dev(kobj);
	struct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	struct fw_priv *fw_priv;
	ssize_t ret_count;

	mutex_lock(&fw_lock);
	fw_priv = fw_sysfs->fw_priv;
	if (!fw_priv || fw_sysfs_done(fw_priv)) {
		ret_count = -ENODEV;
		goto out;
	}
	if (offset > fw_priv->size) {
		ret_count = 0;
		goto out;
	}
	if (count > fw_priv->size - offset)
		count = fw_priv->size - offset;

	ret_count = count;

	if (fw_priv->data)
		firmware_rw_data(fw_priv, buffer, offset, count, true);
	else
		firmware_rw(fw_priv, buffer, offset, count, true);

out:
	mutex_unlock(&fw_lock);
	return ret_count;
}