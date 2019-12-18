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
struct xenisrc {size_t xi_port; int /*<<< orphan*/  xi_pirq; scalar_t__ xi_edgetrigger; } ;
struct physdev_irq_status_query {int flags; int /*<<< orphan*/  irq; } ;
struct intsrc {int dummy; } ;
struct evtchn_bind_pirq {size_t port; int /*<<< orphan*/  flags; int /*<<< orphan*/  pirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_PIRQ__WILL_SHARE ; 
 int /*<<< orphan*/  EVTCHNOP_bind_pirq ; 
 int HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_pirq*) ; 
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_irq_status_query*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PHYSDEVOP_irq_status_query ; 
 int XENIRQSTAT_needs_eoi ; 
 int /*<<< orphan*/  evtchn_unmask_port (size_t) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_intr_isrc_lock ; 
 int /*<<< orphan*/  xen_intr_pirq_eoi_map ; 
 int /*<<< orphan*/  xen_intr_pirq_eoi_map_enabled ; 
 struct xenisrc** xen_intr_port_to_isrc ; 
 int /*<<< orphan*/  xen_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xen_intr_pirq_enable_intr(struct intsrc *base_isrc)
{
	struct xenisrc *isrc;
	struct evtchn_bind_pirq bind_pirq;
	struct physdev_irq_status_query irq_status;
	int error;

	isrc = (struct xenisrc *)base_isrc;

	if (!xen_intr_pirq_eoi_map_enabled) {
		irq_status.irq = isrc->xi_pirq;
		error = HYPERVISOR_physdev_op(PHYSDEVOP_irq_status_query,
		    &irq_status);
		if (error)
			panic("unable to get status of IRQ#%d", isrc->xi_pirq);

		if (irq_status.flags & XENIRQSTAT_needs_eoi) {
			/*
			 * Since the dynamic PIRQ EOI map is not available
			 * mark the PIRQ as needing EOI unconditionally.
			 */
			xen_set_bit(isrc->xi_pirq, xen_intr_pirq_eoi_map);
		}
	}

	bind_pirq.pirq = isrc->xi_pirq;
	bind_pirq.flags = isrc->xi_edgetrigger ? 0 : BIND_PIRQ__WILL_SHARE;
	error = HYPERVISOR_event_channel_op(EVTCHNOP_bind_pirq, &bind_pirq);
	if (error)
		panic("unable to bind IRQ#%d", isrc->xi_pirq);

	isrc->xi_port = bind_pirq.port;

	mtx_lock(&xen_intr_isrc_lock);
	KASSERT((xen_intr_port_to_isrc[bind_pirq.port] == NULL),
	    ("trying to override an already setup event channel port"));
	xen_intr_port_to_isrc[bind_pirq.port] = isrc;
	mtx_unlock(&xen_intr_isrc_lock);

	evtchn_unmask_port(isrc->xi_port);
}