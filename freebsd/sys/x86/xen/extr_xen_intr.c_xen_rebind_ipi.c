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
struct xenisrc {int xi_cpu; size_t xi_port; int /*<<< orphan*/  xi_intsrc; } ;
struct evtchn_bind_ipi {int vcpu; size_t port; } ;
struct TYPE_2__ {int pc_vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_bind_ipi ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_ipi*) ; 
 int /*<<< orphan*/ * cpu_apic_ids ; 
 int /*<<< orphan*/  evtchn_unmask_port (size_t) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 TYPE_1__* pcpu_find (int) ; 
 int xen_intr_assign_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xenisrc** xen_intr_port_to_isrc ; 

__attribute__((used)) static void
xen_rebind_ipi(struct xenisrc *isrc)
{
#ifdef SMP
	int cpu = isrc->xi_cpu;
	int vcpu_id = pcpu_find(cpu)->pc_vcpu_id;
	int error;
	struct evtchn_bind_ipi bind_ipi = { .vcpu = vcpu_id };

	error = HYPERVISOR_event_channel_op(EVTCHNOP_bind_ipi,
	                                    &bind_ipi);
	if (error != 0)
		panic("unable to rebind xen IPI: %d", error);

	isrc->xi_port = bind_ipi.port;
	isrc->xi_cpu = 0;
	xen_intr_port_to_isrc[bind_ipi.port] = isrc;

	error = xen_intr_assign_cpu(&isrc->xi_intsrc,
	                            cpu_apic_ids[cpu]);
	if (error)
		panic("unable to bind xen IPI to CPU#%d: %d",
		      cpu, error);

	evtchn_unmask_port(bind_ipi.port);
#else
	panic("Resume IPI event channel on UP");
#endif
}