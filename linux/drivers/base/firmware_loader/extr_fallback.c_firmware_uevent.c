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
struct kobj_uevent_env {int dummy; } ;
struct fw_sysfs {scalar_t__ fw_priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int do_firmware_uevent (struct fw_sysfs*,struct kobj_uevent_env*) ; 
 int /*<<< orphan*/  fw_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fw_sysfs* to_fw_sysfs (struct device*) ; 

__attribute__((used)) static int firmware_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	int err = 0;

	mutex_lock(&fw_lock);
	if (fw_sysfs->fw_priv)
		err = do_firmware_uevent(fw_sysfs, env);
	mutex_unlock(&fw_lock);
	return err;
}