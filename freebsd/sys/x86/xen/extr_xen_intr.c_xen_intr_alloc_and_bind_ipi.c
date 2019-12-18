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
typedef  int /*<<< orphan*/  xen_intr_handle_t ;
typedef  int u_int ;
struct xenisrc {int xi_cpu; int xi_close; int /*<<< orphan*/  xi_intsrc; } ;
struct evtchn_bind_ipi {int vcpu; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  name ;
typedef  struct evtchn_bind_ipi evtchn_close_t ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  driver_filter_t ;
struct TYPE_2__ {int pc_vcpu_id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVTCHNOP_bind_ipi ; 
 int /*<<< orphan*/  EVTCHNOP_close ; 
 int /*<<< orphan*/  EVTCHN_TYPE_IPI ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_ipi*) ; 
 int /*<<< orphan*/  MAXCOMLEN ; 
 int /*<<< orphan*/ * cpu_apic_ids ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* pcpu_find (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  xen_intr_assign_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xen_intr_bind_isrc (struct xenisrc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_intr_unbind (int /*<<< orphan*/ ) ; 

int
xen_intr_alloc_and_bind_ipi(u_int cpu, driver_filter_t filter,
    enum intr_type flags, xen_intr_handle_t *port_handlep)
{
#ifdef SMP
	int vcpu_id = pcpu_find(cpu)->pc_vcpu_id;
	struct xenisrc *isrc;
	struct evtchn_bind_ipi bind_ipi = { .vcpu = vcpu_id };
	/* Same size as the one used by intr_handler->ih_name. */
	char name[MAXCOMLEN + 1];
	int error;

	isrc = NULL;
	error = HYPERVISOR_event_channel_op(EVTCHNOP_bind_ipi, &bind_ipi);
	if (error != 0) {
		/*
		 * XXX Trap Hypercall error code Linuxisms in
		 *     the HYPERCALL layer.
		 */
		return (-error);
	}

	snprintf(name, sizeof(name), "cpu%u", cpu);

	error = xen_intr_bind_isrc(&isrc, bind_ipi.port, EVTCHN_TYPE_IPI,
	    name, filter, NULL, NULL, flags, port_handlep);
	if (error != 0) {
		evtchn_close_t close = { .port = bind_ipi.port };

		xen_intr_unbind(*port_handlep);
		if (HYPERVISOR_event_channel_op(EVTCHNOP_close, &close))
			panic("EVTCHNOP_close failed");
		return (error);
	}

	if (isrc->xi_cpu != cpu) {
		/*
		 * Too early in the boot process for the generic interrupt
		 * code to perform the binding.  Update our event channel
		 * masks manually so events can't fire on the wrong cpu
		 * during AP startup.
		 */
		xen_intr_assign_cpu(&isrc->xi_intsrc, cpu_apic_ids[cpu]);
	}

	/*
	 * The Event Channel API opened this port, so it is
	 * responsible for closing it automatically on unbind.
	 */
	isrc->xi_close = 1;
	return (0);
#else
	return (EOPNOTSUPP);
#endif
}