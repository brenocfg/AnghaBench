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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct kvmppc_xics {int dummy; } ;
struct kvmppc_ics {struct ics_irq_state* irq_state; } ;
struct ics_irq_state {scalar_t__ pq_state; int /*<<< orphan*/  intr_cpu; scalar_t__ host_irq; scalar_t__ lsi; int /*<<< orphan*/  exists; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KVM_INTERRUPT_SET ; 
 scalar_t__ KVM_INTERRUPT_SET_LEVEL ; 
 scalar_t__ KVM_INTERRUPT_UNSET ; 
 scalar_t__ PQ_PRESENTED ; 
 int /*<<< orphan*/  XICS_DBG (char*,scalar_t__,...) ; 
 scalar_t__ cmpxchg (scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  icp_deliver_irq (struct kvmppc_xics*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct kvmppc_ics* kvmppc_xics_find_ics (struct kvmppc_xics*,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static int ics_deliver_irq(struct kvmppc_xics *xics, u32 irq, u32 level)
{
	struct ics_irq_state *state;
	struct kvmppc_ics *ics;
	u16 src;
	u32 pq_old, pq_new;

	XICS_DBG("ics deliver %#x (level: %d)\n", irq, level);

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	if (!ics) {
		XICS_DBG("ics_deliver_irq: IRQ 0x%06x not found !\n", irq);
		return -EINVAL;
	}
	state = &ics->irq_state[src];
	if (!state->exists)
		return -EINVAL;

	if (level == KVM_INTERRUPT_SET_LEVEL || level == KVM_INTERRUPT_SET)
		level = 1;
	else if (level == KVM_INTERRUPT_UNSET)
		level = 0;
	/*
	 * Take other values the same as 1, consistent with original code.
	 * maybe WARN here?
	 */

	if (!state->lsi && level == 0) /* noop for MSI */
		return 0;

	do {
		pq_old = state->pq_state;
		if (state->lsi) {
			if (level) {
				if (pq_old & PQ_PRESENTED)
					/* Setting already set LSI ... */
					return 0;

				pq_new = PQ_PRESENTED;
			} else
				pq_new = 0;
		} else
			pq_new = ((pq_old << 1) & 3) | PQ_PRESENTED;
	} while (cmpxchg(&state->pq_state, pq_old, pq_new) != pq_old);

	/* Test P=1, Q=0, this is the only case where we present */
	if (pq_new == PQ_PRESENTED)
		icp_deliver_irq(xics, NULL, irq, false);

	/* Record which CPU this arrived on for passed-through interrupts */
	if (state->host_irq)
		state->intr_cpu = raw_smp_processor_id();

	return 0;
}