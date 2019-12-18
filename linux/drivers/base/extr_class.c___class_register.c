#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ktype; void* kset; } ;
struct TYPE_3__ {TYPE_2__ kobj; } ;
struct subsys_private {TYPE_1__ subsys; struct class* class; int /*<<< orphan*/  mutex; int /*<<< orphan*/  glue_dirs; int /*<<< orphan*/  interfaces; int /*<<< orphan*/  klist_devices; } ;
struct lock_class_key {int dummy; } ;
struct class {int /*<<< orphan*/  class_groups; struct subsys_private* p; scalar_t__ dev_kobj; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __mutex_init (int /*<<< orphan*/ *,char*,struct lock_class_key*) ; 
 struct class block_class ; 
 int class_add_groups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_get (struct class*) ; 
 void* class_kset ; 
 int /*<<< orphan*/  class_ktype ; 
 int /*<<< orphan*/  class_put (struct class*) ; 
 int /*<<< orphan*/  kfree (struct subsys_private*) ; 
 int /*<<< orphan*/  klist_class_dev_get ; 
 int /*<<< orphan*/  klist_class_dev_put ; 
 int /*<<< orphan*/  klist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kobject_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kset_init (int /*<<< orphan*/ *) ; 
 int kset_register (TYPE_1__*) ; 
 struct subsys_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_deprecated ; 
 scalar_t__ sysfs_dev_char_kobj ; 

int __class_register(struct class *cls, struct lock_class_key *key)
{
	struct subsys_private *cp;
	int error;

	pr_debug("device class '%s': registering\n", cls->name);

	cp = kzalloc(sizeof(*cp), GFP_KERNEL);
	if (!cp)
		return -ENOMEM;
	klist_init(&cp->klist_devices, klist_class_dev_get, klist_class_dev_put);
	INIT_LIST_HEAD(&cp->interfaces);
	kset_init(&cp->glue_dirs);
	__mutex_init(&cp->mutex, "subsys mutex", key);
	error = kobject_set_name(&cp->subsys.kobj, "%s", cls->name);
	if (error) {
		kfree(cp);
		return error;
	}

	/* set the default /sys/dev directory for devices of this class */
	if (!cls->dev_kobj)
		cls->dev_kobj = sysfs_dev_char_kobj;

#if defined(CONFIG_BLOCK)
	/* let the block class directory show up in the root of sysfs */
	if (!sysfs_deprecated || cls != &block_class)
		cp->subsys.kobj.kset = class_kset;
#else
	cp->subsys.kobj.kset = class_kset;
#endif
	cp->subsys.kobj.ktype = &class_ktype;
	cp->class = cls;
	cls->p = cp;

	error = kset_register(&cp->subsys);
	if (error) {
		kfree(cp);
		return error;
	}
	error = class_add_groups(class_get(cls), cls->class_groups);
	class_put(cls);
	return error;
}