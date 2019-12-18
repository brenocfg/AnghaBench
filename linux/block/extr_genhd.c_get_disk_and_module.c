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
struct module {int dummy; } ;
struct kobject {int dummy; } ;
struct gendisk {TYPE_1__* fops; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {struct module* owner; } ;

/* Variables and functions */
 TYPE_2__* disk_to_dev (struct gendisk*) ; 
 struct kobject* kobject_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

struct kobject *get_disk_and_module(struct gendisk *disk)
{
	struct module *owner;
	struct kobject *kobj;

	if (!disk->fops)
		return NULL;
	owner = disk->fops->owner;
	if (owner && !try_module_get(owner))
		return NULL;
	kobj = kobject_get_unless_zero(&disk_to_dev(disk)->kobj);
	if (kobj == NULL) {
		module_put(owner);
		return NULL;
	}
	return kobj;

}