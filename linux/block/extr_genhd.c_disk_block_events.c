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
struct gendisk {struct disk_events* ev; } ;
struct disk_events {int /*<<< orphan*/  block_mutex; int /*<<< orphan*/  dwork; int /*<<< orphan*/  lock; int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void disk_block_events(struct gendisk *disk)
{
	struct disk_events *ev = disk->ev;
	unsigned long flags;
	bool cancel;

	if (!ev)
		return;

	/*
	 * Outer mutex ensures that the first blocker completes canceling
	 * the event work before further blockers are allowed to finish.
	 */
	mutex_lock(&ev->block_mutex);

	spin_lock_irqsave(&ev->lock, flags);
	cancel = !ev->block++;
	spin_unlock_irqrestore(&ev->lock, flags);

	if (cancel)
		cancel_delayed_work_sync(&disk->ev->dwork);

	mutex_unlock(&ev->block_mutex);
}