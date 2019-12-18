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
struct mpic_msgr {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mpic_msgr_disable (struct mpic_msgr*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mpic_msgr_disable(struct mpic_msgr *msgr)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&msgr->lock, flags);
	_mpic_msgr_disable(msgr);
	raw_spin_unlock_irqrestore(&msgr->lock, flags);
}