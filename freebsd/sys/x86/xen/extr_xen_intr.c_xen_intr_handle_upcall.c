#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  evtchn_pending_sel; scalar_t__ evtchn_upcall_pending; } ;
typedef  TYPE_1__ vcpu_info_t ;
typedef  unsigned long u_long ;
typedef  scalar_t__ u_int ;
struct xenisrc {scalar_t__ xi_cpu; int /*<<< orphan*/  xi_intsrc; } ;
struct xen_intr_pcpu_data {scalar_t__ last_processed_l1i; scalar_t__ last_processed_l2i; int /*<<< orphan*/ * evtchn_intrcnt; } ;
struct trapframe {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * evtchn_pending; } ;
typedef  TYPE_2__ shared_info_t ;

/* Variables and functions */
 TYPE_1__* DPCPU_GET (int /*<<< orphan*/ ) ; 
 struct xen_intr_pcpu_data* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 TYPE_2__* HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ LONG_BIT ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 unsigned long atomic_readandclear_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int ffsl (unsigned long) ; 
 int /*<<< orphan*/  intr_execute_handlers (int /*<<< orphan*/ *,struct trapframe*) ; 
 int /*<<< orphan*/  lapic_eoi () ; 
 int /*<<< orphan*/  synch_clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_info ; 
 int /*<<< orphan*/  wmb () ; 
 scalar_t__ xen_evtchn_needs_ack ; 
 scalar_t__ xen_hvm_domain () ; 
 unsigned long xen_intr_active_ports (struct xen_intr_pcpu_data*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xen_intr_pcpu ; 
 struct xenisrc** xen_intr_port_to_isrc ; 
 int /*<<< orphan*/  xen_vector_callback_enabled ; 

void
xen_intr_handle_upcall(struct trapframe *trap_frame)
{
	u_int l1i, l2i, port, cpu;
	u_long masked_l1, masked_l2;
	struct xenisrc *isrc;
	shared_info_t *s;
	vcpu_info_t *v;
	struct xen_intr_pcpu_data *pc;
	u_long l1, l2;

	/*
	 * Disable preemption in order to always check and fire events
	 * on the right vCPU
	 */
	critical_enter();

	cpu = PCPU_GET(cpuid);
	pc  = DPCPU_PTR(xen_intr_pcpu);
	s   = HYPERVISOR_shared_info;
	v   = DPCPU_GET(vcpu_info);

	if (xen_hvm_domain() && !xen_vector_callback_enabled) {
		KASSERT((cpu == 0), ("Fired PCI event callback on wrong CPU"));
	}

	v->evtchn_upcall_pending = 0;

#if 0
#ifndef CONFIG_X86 /* No need for a barrier -- XCHG is a barrier on x86. */
	/* Clear master flag /before/ clearing selector flag. */
	wmb();
#endif
#endif

	l1 = atomic_readandclear_long(&v->evtchn_pending_sel);

	l1i = pc->last_processed_l1i;
	l2i = pc->last_processed_l2i;
	(*pc->evtchn_intrcnt)++;

	while (l1 != 0) {

		l1i = (l1i + 1) % LONG_BIT;
		masked_l1 = l1 & ((~0UL) << l1i);

		if (masked_l1 == 0) {
			/*
			 * if we masked out all events, wrap around
			 * to the beginning.
			 */
			l1i = LONG_BIT - 1;
			l2i = LONG_BIT - 1;
			continue;
		}
		l1i = ffsl(masked_l1) - 1;

		do {
			l2 = xen_intr_active_ports(pc, s, l1i);

			l2i = (l2i + 1) % LONG_BIT;
			masked_l2 = l2 & ((~0UL) << l2i);

			if (masked_l2 == 0) {
				/* if we masked out all events, move on */
				l2i = LONG_BIT - 1;
				break;
			}
			l2i = ffsl(masked_l2) - 1;

			/* process port */
			port = (l1i * LONG_BIT) + l2i;
			synch_clear_bit(port, &s->evtchn_pending[0]);

			isrc = xen_intr_port_to_isrc[port];
			if (__predict_false(isrc == NULL))
				continue;

			/* Make sure we are firing on the right vCPU */
			KASSERT((isrc->xi_cpu == PCPU_GET(cpuid)),
				("Received unexpected event on vCPU#%d, event bound to vCPU#%d",
				PCPU_GET(cpuid), isrc->xi_cpu));

			intr_execute_handlers(&isrc->xi_intsrc, trap_frame);

			/*
			 * If this is the final port processed,
			 * we'll pick up here+1 next time.
			 */
			pc->last_processed_l1i = l1i;
			pc->last_processed_l2i = l2i;

		} while (l2i != LONG_BIT - 1);

		l2 = xen_intr_active_ports(pc, s, l1i);
		if (l2 == 0) {
			/*
			 * We handled all ports, so we can clear the
			 * selector bit.
			 */
			l1 &= ~(1UL << l1i);
		}
	}

	if (xen_evtchn_needs_ack)
		lapic_eoi();

	critical_exit();
}