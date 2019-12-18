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
struct ace_device {int fsm_continue_flag; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ace_fsm_dostate (struct ace_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ace_fsm_tasklet(unsigned long data)
{
	struct ace_device *ace = (void *)data;
	unsigned long flags;

	spin_lock_irqsave(&ace->lock, flags);

	/* Loop over state machine until told to stop */
	ace->fsm_continue_flag = 1;
	while (ace->fsm_continue_flag)
		ace_fsm_dostate(ace);

	spin_unlock_irqrestore(&ace->lock, flags);
}