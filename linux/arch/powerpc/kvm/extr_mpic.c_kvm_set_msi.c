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
struct openpic {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct kvm_kernel_irq_routing_entry {TYPE_2__ msi; } ;
struct TYPE_3__ {struct openpic* mpic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSIIR_OFFSET ; 
 int /*<<< orphan*/  openpic_msi_write (struct openpic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int kvm_set_msi(struct kvm_kernel_irq_routing_entry *e,
		struct kvm *kvm, int irq_source_id, int level, bool line_status)
{
	struct openpic *opp = kvm->arch.mpic;
	unsigned long flags;

	spin_lock_irqsave(&opp->lock, flags);

	/*
	 * XXX We ignore the target address for now, as we only support
	 *     a single MSI bank.
	 */
	openpic_msi_write(kvm->arch.mpic, MSIIR_OFFSET, e->msi.data);
	spin_unlock_irqrestore(&opp->lock, flags);

	/* All code paths we care about don't check for the return value */
	return 0;
}