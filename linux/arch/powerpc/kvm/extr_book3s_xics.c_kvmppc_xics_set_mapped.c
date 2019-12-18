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
typedef  size_t u16 ;
struct kvmppc_xics {int dummy; } ;
struct kvmppc_ics {TYPE_2__* irq_state; } ;
struct TYPE_3__ {struct kvmppc_xics* xics; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_4__ {unsigned long host_irq; int intr_cpu; } ;

/* Variables and functions */
 struct kvmppc_ics* kvmppc_xics_find_ics (struct kvmppc_xics*,unsigned long,size_t*) ; 

void kvmppc_xics_set_mapped(struct kvm *kvm, unsigned long irq,
			    unsigned long host_irq)
{
	struct kvmppc_xics *xics = kvm->arch.xics;
	struct kvmppc_ics *ics;
	u16 idx;

	ics = kvmppc_xics_find_ics(xics, irq, &idx);
	if (!ics)
		return;

	ics->irq_state[idx].host_irq = host_irq;
	ics->irq_state[idx].intr_cpu = -1;
}