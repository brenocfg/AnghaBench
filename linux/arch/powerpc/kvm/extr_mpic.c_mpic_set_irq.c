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
typedef  int /*<<< orphan*/  u32 ;
struct openpic {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  pin; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ irqchip; } ;
struct TYPE_4__ {struct openpic* mpic; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  openpic_set_irq (struct openpic*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mpic_set_irq(struct kvm_kernel_irq_routing_entry *e,
			struct kvm *kvm, int irq_source_id, int level,
			bool line_status)
{
	u32 irq = e->irqchip.pin;
	struct openpic *opp = kvm->arch.mpic;
	unsigned long flags;

	spin_lock_irqsave(&opp->lock, flags);
	openpic_set_irq(opp, irq, level);
	spin_unlock_irqrestore(&opp->lock, flags);

	/* All code paths we care about don't check for the return value */
	return 0;
}