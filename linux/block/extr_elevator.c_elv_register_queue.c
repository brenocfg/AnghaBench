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
struct request_queue {int /*<<< orphan*/  kobj; struct elevator_queue* elevator; } ;
struct TYPE_4__ {scalar_t__ name; } ;
struct elv_fs_entry {TYPE_2__ attr; } ;
struct elevator_queue {int registered; int /*<<< orphan*/  kobj; TYPE_1__* type; } ;
struct TYPE_3__ {struct elv_fs_entry* elevator_attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_create_file (int /*<<< orphan*/ *,TYPE_2__*) ; 

int elv_register_queue(struct request_queue *q, bool uevent)
{
	struct elevator_queue *e = q->elevator;
	int error;

	error = kobject_add(&e->kobj, &q->kobj, "%s", "iosched");
	if (!error) {
		struct elv_fs_entry *attr = e->type->elevator_attrs;
		if (attr) {
			while (attr->attr.name) {
				if (sysfs_create_file(&e->kobj, &attr->attr))
					break;
				attr++;
			}
		}
		if (uevent)
			kobject_uevent(&e->kobj, KOBJ_ADD);

		e->registered = 1;
	}
	return error;
}