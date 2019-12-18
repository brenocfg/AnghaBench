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
struct floppy_state {scalar_t__ state; int /*<<< orphan*/  wanted; int /*<<< orphan*/  wait; } ;
typedef  enum swim_state { ____Placeholder_swim_state } swim_state ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ available ; 
 scalar_t__ idle ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  swim3_dbg (char*,char*) ; 
 int /*<<< orphan*/  swim3_lock ; 
 scalar_t__ wait_event_interruptible_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int grab_drive(struct floppy_state *fs, enum swim_state state,
		      int interruptible)
{
	unsigned long flags;

	swim3_dbg("%s", "-> grab drive\n");

	spin_lock_irqsave(&swim3_lock, flags);
	if (fs->state != idle && fs->state != available) {
		++fs->wanted;
		/* this will enable irqs in order to sleep */
		if (!interruptible)
			wait_event_lock_irq(fs->wait,
                                        fs->state == available,
                                        swim3_lock);
		else if (wait_event_interruptible_lock_irq(fs->wait,
					fs->state == available,
					swim3_lock)) {
			--fs->wanted;
			spin_unlock_irqrestore(&swim3_lock, flags);
			return -EINTR;
		}
		--fs->wanted;
	}
	fs->state = state;
	spin_unlock_irqrestore(&swim3_lock, flags);

	return 0;
}