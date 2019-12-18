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
struct gendisk {TYPE_1__* ev; int /*<<< orphan*/  disk_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  __disk_unblock_events (struct gendisk*,int) ; 
 int /*<<< orphan*/  disk_events ; 
 int /*<<< orphan*/  disk_events_attrs ; 
 int /*<<< orphan*/  disk_events_mutex ; 
 TYPE_2__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_create_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disk_add_events(struct gendisk *disk)
{
	/* FIXME: error handling */
	if (sysfs_create_files(&disk_to_dev(disk)->kobj, disk_events_attrs) < 0)
		pr_warn("%s: failed to create sysfs files for events\n",
			disk->disk_name);

	if (!disk->ev)
		return;

	mutex_lock(&disk_events_mutex);
	list_add_tail(&disk->ev->node, &disk_events);
	mutex_unlock(&disk_events_mutex);

	/*
	 * Block count is initialized to 1 and the following initial
	 * unblock kicks it into action.
	 */
	__disk_unblock_events(disk, true);
}