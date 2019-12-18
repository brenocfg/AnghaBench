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
struct gendisk {int /*<<< orphan*/  integrity_kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 TYPE_1__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  integrity_ktype ; 
 scalar_t__ kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void blk_integrity_add(struct gendisk *disk)
{
	if (kobject_init_and_add(&disk->integrity_kobj, &integrity_ktype,
				 &disk_to_dev(disk)->kobj, "%s", "integrity"))
		return;

	kobject_uevent(&disk->integrity_kobj, KOBJ_ADD);
}