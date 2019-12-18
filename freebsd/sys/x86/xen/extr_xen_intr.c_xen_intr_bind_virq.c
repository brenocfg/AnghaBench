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
typedef  int /*<<< orphan*/  xen_intr_handle_t ;
typedef  size_t u_int ;
struct TYPE_3__ {int /*<<< orphan*/  is_event; } ;
struct xenisrc {size_t xi_cpu; int xi_close; size_t xi_virq; TYPE_1__ xi_intsrc; } ;
struct evtchn_bind_virq {size_t virq; int vcpu; int /*<<< orphan*/  port; } ;
typedef  struct evtchn_bind_virq evtchn_close_t ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int pc_vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_bind_virq ; 
 int /*<<< orphan*/  EVTCHNOP_close ; 
 int /*<<< orphan*/  EVTCHN_TYPE_VIRQ ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_virq*) ; 
 int /*<<< orphan*/ * cpu_apic_ids ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int intr_event_bind (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_2__* pcpu_find (size_t) ; 
 int /*<<< orphan*/  xen_intr_assign_cpu (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int xen_intr_bind_isrc (struct xenisrc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_intr_unbind (int /*<<< orphan*/ ) ; 

int 
xen_intr_bind_virq(device_t dev, u_int virq, u_int cpu,
    driver_filter_t filter, driver_intr_t handler, void *arg,
    enum intr_type flags, xen_intr_handle_t *port_handlep)
{
	int vcpu_id = pcpu_find(cpu)->pc_vcpu_id;
	struct xenisrc *isrc;
	struct evtchn_bind_virq bind_virq = { .virq = virq, .vcpu = vcpu_id };
	int error;

	isrc = NULL;
	error = HYPERVISOR_event_channel_op(EVTCHNOP_bind_virq, &bind_virq);
	if (error != 0) {
		/*
		 * XXX Trap Hypercall error code Linuxisms in
		 *     the HYPERCALL layer.
		 */
		return (-error);
	}

	error = xen_intr_bind_isrc(&isrc, bind_virq.port, EVTCHN_TYPE_VIRQ,
	    device_get_nameunit(dev), filter, handler, arg, flags,
	    port_handlep);

#ifdef SMP
	if (error == 0)
		error = intr_event_bind(isrc->xi_intsrc.is_event, cpu);
#endif

	if (error != 0) {
		evtchn_close_t close = { .port = bind_virq.port };

		xen_intr_unbind(*port_handlep);
		if (HYPERVISOR_event_channel_op(EVTCHNOP_close, &close))
			panic("EVTCHNOP_close failed");
		return (error);
	}

#ifdef SMP
	if (isrc->xi_cpu != cpu) {
		/*
		 * Too early in the boot process for the generic interrupt
		 * code to perform the binding.  Update our event channel
		 * masks manually so events can't fire on the wrong cpu
		 * during AP startup.
		 */
		xen_intr_assign_cpu(&isrc->xi_intsrc, cpu_apic_ids[cpu]);
	}
#endif

	/*
	 * The Event Channel API opened this port, so it is
	 * responsible for closing it automatically on unbind.
	 */
	isrc->xi_close = 1;
	isrc->xi_virq = virq;

	return (0);
}