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
struct subscription {int /*<<< orphan*/  sm; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  last_event_failed; } ;
struct http_client {int dummy; } ;
typedef  enum http_client_event { ____Placeholder_http_client_event } http_client_event ;
struct TYPE_2__ {int /*<<< orphan*/  num_failures; int /*<<< orphan*/  domain_and_port; } ;

/* Variables and functions */
#define  HTTP_CLIENT_FAILED 131 
#define  HTTP_CLIENT_INVALID_REPLY 130 
#define  HTTP_CLIENT_OK 129 
#define  HTTP_CLIENT_TIMEOUT 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_addr_failure (struct wps_event_*) ; 
 int /*<<< orphan*/  event_delete (struct wps_event_*) ; 
 int /*<<< orphan*/  event_send_all_later (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void event_http_cb(void *ctx, struct http_client *c,
			  enum http_client_event event)
{
	struct wps_event_ *e = ctx;
	struct subscription *s = e->s;

	wpa_printf(MSG_DEBUG, "WPS UPnP: HTTP client callback: e=%p c=%p "
		   "event=%d", e, c, event);
	switch (event) {
	case HTTP_CLIENT_OK:
		wpa_printf(MSG_DEBUG,
			   "WPS UPnP: Got event %p reply OK from %s",
			   e, e->addr->domain_and_port);
		e->addr->num_failures = 0;
		s->last_event_failed = 0;
		event_delete(e);

		/* Schedule sending more if there is more to send */
		if (!dl_list_empty(&s->event_queue))
			event_send_all_later(s->sm);
		break;
	case HTTP_CLIENT_FAILED:
		wpa_printf(MSG_DEBUG, "WPS UPnP: Event send failure");
		event_addr_failure(e);
		break;
	case HTTP_CLIENT_INVALID_REPLY:
		wpa_printf(MSG_DEBUG, "WPS UPnP: Invalid reply");
		event_addr_failure(e);
		break;
	case HTTP_CLIENT_TIMEOUT:
		wpa_printf(MSG_DEBUG, "WPS UPnP: Event send timeout");
		event_addr_failure(e);
		break;
	}
}