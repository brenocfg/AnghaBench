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
typedef  int u32 ;
struct mpic_msgr {int num; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int _mpic_msgr_mer_read (struct mpic_msgr*) ; 
 int /*<<< orphan*/  _mpic_msgr_mer_write (struct mpic_msgr*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mpic_msgr_enable(struct mpic_msgr *msgr)
{
	unsigned long flags;
	u32 mer;

	raw_spin_lock_irqsave(&msgr->lock, flags);
	mer = _mpic_msgr_mer_read(msgr);
	_mpic_msgr_mer_write(msgr, mer | (1 << msgr->num));
	raw_spin_unlock_irqrestore(&msgr->lock, flags);
}