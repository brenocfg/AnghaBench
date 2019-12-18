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
struct request_queue {int dummy; } ;
struct floppy_state {size_t index; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (struct request_queue*) ; 
 TYPE_1__** disks ; 
 int /*<<< orphan*/  idle ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  swim3_dbg (char*,char*) ; 
 int /*<<< orphan*/  swim3_lock ; 

__attribute__((used)) static void release_drive(struct floppy_state *fs)
{
	struct request_queue *q = disks[fs->index]->queue;
	unsigned long flags;

	swim3_dbg("%s", "-> release drive\n");

	spin_lock_irqsave(&swim3_lock, flags);
	fs->state = idle;
	spin_unlock_irqrestore(&swim3_lock, flags);

	blk_mq_freeze_queue(q);
	blk_mq_quiesce_queue(q);
	blk_mq_unquiesce_queue(q);
	blk_mq_unfreeze_queue(q);
}