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
typedef  int /*<<< orphan*/ * xen_intr_handle_t ;
typedef  size_t evtchn_port_t ;
struct TYPE_2__ {int /*<<< orphan*/  xi_vector; int /*<<< orphan*/  xi_refcount; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NR_EVENT_CHANNELS ; 
 int /*<<< orphan*/  is_valid_evtchn (size_t) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_intr_isrc_lock ; 
 TYPE_1__** xen_intr_port_to_isrc ; 

int
xen_intr_get_evtchn_from_port(evtchn_port_t port, xen_intr_handle_t *handlep)
{

	if (!is_valid_evtchn(port) || port >= NR_EVENT_CHANNELS)
		return (EINVAL);

	if (handlep == NULL) {
		return (EINVAL);
	}

	mtx_lock(&xen_intr_isrc_lock);
	if (xen_intr_port_to_isrc[port] == NULL) {
		mtx_unlock(&xen_intr_isrc_lock);
		return (EINVAL);
	}
	refcount_acquire(&xen_intr_port_to_isrc[port]->xi_refcount);
	mtx_unlock(&xen_intr_isrc_lock);

	/* Assign the opaque handler (the event channel port) */
	*handlep = &xen_intr_port_to_isrc[port]->xi_vector;

	return (0);
}