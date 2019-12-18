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
struct wps_event_ {TYPE_1__* addr; struct subscription* s; } ;
struct subscription {int /*<<< orphan*/  list; int /*<<< orphan*/  addr_list; } ;
struct TYPE_2__ {scalar_t__ num_failures; int /*<<< orphan*/  list; int /*<<< orphan*/  domain_and_port; } ;

/* Variables and functions */
 scalar_t__ MAX_FAILURES ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_retry (struct wps_event_*,int) ; 
 int /*<<< orphan*/  subscr_addr_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  subscription_destroy (struct subscription*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void event_addr_failure(struct wps_event_ *e)
{
	struct subscription *s = e->s;

	e->addr->num_failures++;
	wpa_printf(MSG_DEBUG, "WPS UPnP: Failed to send event %p to %s "
		   "(num_failures=%u)",
		   e, e->addr->domain_and_port, e->addr->num_failures);

	if (e->addr->num_failures < MAX_FAILURES) {
		/* Try other addresses, if available */
		event_retry(e, 1);
		return;
	}

	/*
	 * If other side doesn't like what we say, forget about them.
	 * (There is no way to tell other side that we are dropping them...).
	 */
	wpa_printf(MSG_DEBUG, "WPS UPnP: Deleting subscription %p "
		   "address %s due to errors", s, e->addr->domain_and_port);
	dl_list_del(&e->addr->list);
	subscr_addr_delete(e->addr);
	e->addr = NULL;

	if (dl_list_empty(&s->addr_list)) {
		/* if we've given up on all addresses */
		wpa_printf(MSG_DEBUG, "WPS UPnP: Removing subscription %p "
			   "with no addresses", s);
		dl_list_del(&s->list);
		subscription_destroy(s);
		return;
	}

	/* Try other addresses, if available */
	event_retry(e, 0);
}