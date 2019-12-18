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
struct subsys_interface {int dummy; } ;
struct kobject {int dummy; } ;
struct device {unsigned int id; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int kobject_init_and_add (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  kobject_uevent (struct kobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_percpu_entry ; 
 struct kobject* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct kobject** sq_kobject ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sq_dev_add(struct device *dev, struct subsys_interface *sif)
{
	unsigned int cpu = dev->id;
	struct kobject *kobj;
	int error;

	sq_kobject[cpu] = kzalloc(sizeof(struct kobject), GFP_KERNEL);
	if (unlikely(!sq_kobject[cpu]))
		return -ENOMEM;

	kobj = sq_kobject[cpu];
	error = kobject_init_and_add(kobj, &ktype_percpu_entry, &dev->kobj,
				     "%s", "sq");
	if (!error)
		kobject_uevent(kobj, KOBJ_ADD);
	return error;
}