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
struct cpuidle_state_kobj {int /*<<< orphan*/  kobj; int /*<<< orphan*/  kobj_unregister; struct cpuidle_device* device; int /*<<< orphan*/ * state_usage; int /*<<< orphan*/ * state; } ;
struct cpuidle_driver {int state_count; int /*<<< orphan*/ * states; } ;
struct cpuidle_device_kobj {int /*<<< orphan*/  kobj; } ;
struct cpuidle_device {struct cpuidle_state_kobj** kobjs; int /*<<< orphan*/ * states_usage; struct cpuidle_device_kobj* kobj_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  cpuidle_add_s2idle_attr_group (struct cpuidle_state_kobj*) ; 
 int /*<<< orphan*/  cpuidle_free_state_kobj (struct cpuidle_device*,int) ; 
 struct cpuidle_driver* cpuidle_get_cpu_driver (struct cpuidle_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cpuidle_state_kobj*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_state_cpuidle ; 
 struct cpuidle_state_kobj* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpuidle_add_state_sysfs(struct cpuidle_device *device)
{
	int i, ret = -ENOMEM;
	struct cpuidle_state_kobj *kobj;
	struct cpuidle_device_kobj *kdev = device->kobj_dev;
	struct cpuidle_driver *drv = cpuidle_get_cpu_driver(device);

	/* state statistics */
	for (i = 0; i < drv->state_count; i++) {
		kobj = kzalloc(sizeof(struct cpuidle_state_kobj), GFP_KERNEL);
		if (!kobj) {
			ret = -ENOMEM;
			goto error_state;
		}
		kobj->state = &drv->states[i];
		kobj->state_usage = &device->states_usage[i];
		kobj->device = device;
		init_completion(&kobj->kobj_unregister);

		ret = kobject_init_and_add(&kobj->kobj, &ktype_state_cpuidle,
					   &kdev->kobj, "state%d", i);
		if (ret) {
			kfree(kobj);
			goto error_state;
		}
		cpuidle_add_s2idle_attr_group(kobj);
		kobject_uevent(&kobj->kobj, KOBJ_ADD);
		device->kobjs[i] = kobj;
	}

	return 0;

error_state:
	for (i = i - 1; i >= 0; i--)
		cpuidle_free_state_kobj(device, i);
	return ret;
}