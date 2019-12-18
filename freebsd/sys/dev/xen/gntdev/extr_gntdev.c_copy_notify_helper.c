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
typedef  int /*<<< orphan*/ * xen_intr_handle_t ;
struct notify_data {int action; int /*<<< orphan*/ * notify_evtchn_handle; int /*<<< orphan*/  index; int /*<<< orphan*/  event_channel_port; } ;
struct ioctl_gntdev_unmap_notify {int action; int /*<<< orphan*/  index; int /*<<< orphan*/  event_channel_port; } ;

/* Variables and functions */
 int EINVAL ; 
 int UNMAP_NOTIFY_SEND_EVENT ; 
 scalar_t__ xen_intr_get_evtchn_from_port (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xen_intr_unbind (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
copy_notify_helper(struct notify_data *destination,
    struct ioctl_gntdev_unmap_notify *source)
{
	xen_intr_handle_t handlep = NULL;

	/*
	 * "Get" before "Put"ting previous reference, as we might be
	 * holding the last reference to the event channel port.
	 */
	if (source->action & UNMAP_NOTIFY_SEND_EVENT)
		if (xen_intr_get_evtchn_from_port(source->event_channel_port,
		    &handlep) != 0)
			return (EINVAL);

	if (destination->action & UNMAP_NOTIFY_SEND_EVENT)
		xen_intr_unbind(&destination->notify_evtchn_handle);

	destination->action = source->action;
	destination->event_channel_port = source->event_channel_port;
	destination->index = source->index;
	destination->notify_evtchn_handle = handlep;

	return (0);
}