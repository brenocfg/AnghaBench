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
struct kvmppc_vcore {int /*<<< orphan*/  stoltb_lock; int /*<<< orphan*/  preempt_tb; } ;

/* Variables and functions */
 int /*<<< orphan*/  mftb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kvmppc_core_start_stolen(struct kvmppc_vcore *vc)
{
	unsigned long flags;

	spin_lock_irqsave(&vc->stoltb_lock, flags);
	vc->preempt_tb = mftb();
	spin_unlock_irqrestore(&vc->stoltb_lock, flags);
}