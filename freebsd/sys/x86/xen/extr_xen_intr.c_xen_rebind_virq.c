#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xenisrc {int xi_cpu; size_t xi_port; int /*<<< orphan*/  xi_virq; int /*<<< orphan*/  xi_intsrc; } ;
struct evtchn_bind_virq {int vcpu; size_t port; int /*<<< orphan*/  virq; } ;
struct TYPE_2__ {int pc_vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_bind_virq ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_virq*) ; 
 int /*<<< orphan*/ * cpu_apic_ids ; 
 int /*<<< orphan*/  evtchn_unmask_port (size_t) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int,...) ; 
 TYPE_1__* pcpu_find (int) ; 
 int xen_intr_assign_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xenisrc** xen_intr_port_to_isrc ; 

__attribute__((used)) static void
xen_rebind_virq(struct xenisrc *isrc)
{
	int cpu = isrc->xi_cpu;
	int vcpu_id = pcpu_find(cpu)->pc_vcpu_id;
	int error;
	struct evtchn_bind_virq bind_virq = { .virq = isrc->xi_virq,
	                                      .vcpu = vcpu_id };

	error = HYPERVISOR_event_channel_op(EVTCHNOP_bind_virq,
	                                    &bind_virq);
	if (error != 0)
		panic("unable to rebind xen VIRQ#%d: %d", isrc->xi_virq, error);

	isrc->xi_port = bind_virq.port;
	isrc->xi_cpu = 0;
	xen_intr_port_to_isrc[bind_virq.port] = isrc;

#ifdef SMP
	error = xen_intr_assign_cpu(&isrc->xi_intsrc,
	                            cpu_apic_ids[cpu]);
	if (error)
		panic("unable to bind xen VIRQ#%d to CPU#%d: %d",
		      isrc->xi_virq, cpu, error);
#endif

	evtchn_unmask_port(bind_virq.port);
}