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
struct wps_event_ {int /*<<< orphan*/  list; TYPE_1__* addr; int /*<<< orphan*/  retry; struct subscription* s; } ;
struct upnp_wps_device_sm {int dummy; } ;
struct subscription {int last_event_failed; int /*<<< orphan*/  event_queue; struct upnp_wps_device_sm* sm; int /*<<< orphan*/  addr_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  domain_and_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_clean (struct wps_event_*) ; 
 int /*<<< orphan*/  event_delete (struct wps_event_*) ; 
 int /*<<< orphan*/  event_send_all_later (struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct wps_event_*,...) ; 

__attribute__((used)) static void event_retry(struct wps_event_ *e, int do_next_address)
{
	struct subscription *s = e->s;
	struct upnp_wps_device_sm *sm = s->sm;

	wpa_printf(MSG_DEBUG, "WPS UPnP: Retry event %p for subscription %p",
		   e, s);
	event_clean(e);
	/* will set: s->current_event = NULL; */

	if (do_next_address) {
		e->retry++;
		wpa_printf(MSG_DEBUG, "WPS UPnP: Try address %d", e->retry);
	}
	if (e->retry >= dl_list_len(&s->addr_list)) {
		wpa_printf(MSG_DEBUG, "WPS UPnP: Giving up on sending event "
			   "for %s", e->addr->domain_and_port);
		event_delete(e);
		s->last_event_failed = 1;
		if (!dl_list_empty(&s->event_queue))
			event_send_all_later(s->sm);
		return;
	}
	dl_list_add(&s->event_queue, &e->list);
	event_send_all_later(sm);
}