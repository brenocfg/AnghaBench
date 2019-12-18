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
struct kset {TYPE_1__* uevent_ops; } ;
struct kobject {struct kset* kset; struct kobject* parent; } ;
struct kobj_uevent_env {int envp_idx; char** envp; } ;
struct device_attribute {int dummy; } ;
struct device {struct kobject kobj; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int (* uevent ) (struct kset*,struct kobject*,struct kobj_uevent_env*) ;int /*<<< orphan*/  (* filter ) (struct kset*,struct kobject*) ;} ;

/* Variables and functions */
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct kobj_uevent_env*) ; 
 struct kobj_uevent_env* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct kset*,struct kobject*) ; 
 int stub2 (struct kset*,struct kobject*,struct kobj_uevent_env*) ; 

__attribute__((used)) static ssize_t uevent_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct kobject *top_kobj;
	struct kset *kset;
	struct kobj_uevent_env *env = NULL;
	int i;
	size_t count = 0;
	int retval;

	/* search the kset, the device belongs to */
	top_kobj = &dev->kobj;
	while (!top_kobj->kset && top_kobj->parent)
		top_kobj = top_kobj->parent;
	if (!top_kobj->kset)
		goto out;

	kset = top_kobj->kset;
	if (!kset->uevent_ops || !kset->uevent_ops->uevent)
		goto out;

	/* respect filter */
	if (kset->uevent_ops && kset->uevent_ops->filter)
		if (!kset->uevent_ops->filter(kset, &dev->kobj))
			goto out;

	env = kzalloc(sizeof(struct kobj_uevent_env), GFP_KERNEL);
	if (!env)
		return -ENOMEM;

	/* let the kset specific function add its keys */
	retval = kset->uevent_ops->uevent(kset, &dev->kobj, env);
	if (retval)
		goto out;

	/* copy keys to file */
	for (i = 0; i < env->envp_idx; i++)
		count += sprintf(&buf[count], "%s\n", env->envp[i]);
out:
	kfree(env);
	return count;
}