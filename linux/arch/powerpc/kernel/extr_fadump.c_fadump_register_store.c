#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int dump_registered; TYPE_1__* ops; scalar_t__ dump_active; int /*<<< orphan*/  fadump_enabled; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fadump_unregister ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  fadump_mutex ; 
 TYPE_2__ fw_dump ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int register_fadump () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static ssize_t fadump_register_store(struct kobject *kobj,
					struct kobj_attribute *attr,
					const char *buf, size_t count)
{
	int ret = 0;
	int input = -1;

	if (!fw_dump.fadump_enabled || fw_dump.dump_active)
		return -EPERM;

	if (kstrtoint(buf, 0, &input))
		return -EINVAL;

	mutex_lock(&fadump_mutex);

	switch (input) {
	case 0:
		if (fw_dump.dump_registered == 0) {
			goto unlock_out;
		}

		/* Un-register Firmware-assisted dump */
		pr_debug("Un-register firmware-assisted dump\n");
		fw_dump.ops->fadump_unregister(&fw_dump);
		break;
	case 1:
		if (fw_dump.dump_registered == 1) {
			/* Un-register Firmware-assisted dump */
			fw_dump.ops->fadump_unregister(&fw_dump);
		}
		/* Register Firmware-assisted dump */
		ret = register_fadump();
		break;
	default:
		ret = -EINVAL;
		break;
	}

unlock_out:
	mutex_unlock(&fadump_mutex);
	return ret < 0 ? ret : count;
}