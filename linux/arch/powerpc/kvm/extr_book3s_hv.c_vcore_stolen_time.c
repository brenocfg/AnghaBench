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
typedef  scalar_t__ u64 ;
struct kvmppc_vcore {scalar_t__ stolen_tb; scalar_t__ vcore_state; scalar_t__ preempt_tb; int /*<<< orphan*/  stoltb_lock; } ;

/* Variables and functions */
 scalar_t__ TB_NIL ; 
 scalar_t__ VCORE_INACTIVE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u64 vcore_stolen_time(struct kvmppc_vcore *vc, u64 now)
{
	u64 p;
	unsigned long flags;

	spin_lock_irqsave(&vc->stoltb_lock, flags);
	p = vc->stolen_tb;
	if (vc->vcore_state != VCORE_INACTIVE &&
	    vc->preempt_tb != TB_NIL)
		p += now - vc->preempt_tb;
	spin_unlock_irqrestore(&vc->stoltb_lock, flags);
	return p;
}