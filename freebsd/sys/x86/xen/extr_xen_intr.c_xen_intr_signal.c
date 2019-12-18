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
typedef  int /*<<< orphan*/  xen_intr_handle_t ;
struct xenisrc {scalar_t__ xi_type; int /*<<< orphan*/  xi_port; } ;
struct evtchn_send {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_send ; 
 scalar_t__ EVTCHN_TYPE_IPI ; 
 scalar_t__ EVTCHN_TYPE_PORT ; 
 int /*<<< orphan*/  HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_send*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct xenisrc* xen_intr_isrc (int /*<<< orphan*/ ) ; 

void
xen_intr_signal(xen_intr_handle_t handle)
{
	struct xenisrc *isrc;

	isrc = xen_intr_isrc(handle);
	if (isrc != NULL) {
		KASSERT(isrc->xi_type == EVTCHN_TYPE_PORT ||
			isrc->xi_type == EVTCHN_TYPE_IPI,
			("evtchn_signal on something other than a local port"));
		struct evtchn_send send = { .port = isrc->xi_port };
		(void)HYPERVISOR_event_channel_op(EVTCHNOP_send, &send);
	}
}