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
struct wps_event_ {int /*<<< orphan*/  list; scalar_t__ subscriber_sequence; int /*<<< orphan*/ * data; struct subscription* s; } ;
struct wpabuf {int dummy; } ;
struct subscription {scalar_t__ next_subscriber_sequence; int /*<<< orphan*/  sm; int /*<<< orphan*/  event_queue; scalar_t__ last_event_failed; } ;

/* Variables and functions */
 unsigned int MAX_EVENTS_QUEUED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 unsigned int dl_list_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_delete (struct wps_event_*) ; 
 struct wps_event_* event_dequeue (struct subscription*) ; 
 int /*<<< orphan*/  event_send_all_later (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct wps_event_*) ; 
 struct wps_event_* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_dup (struct wpabuf const*) ; 

int event_add(struct subscription *s, const struct wpabuf *data, int probereq)
{
	struct wps_event_ *e;
	unsigned int len;

	len = dl_list_len(&s->event_queue);
	if (len >= MAX_EVENTS_QUEUED) {
		wpa_printf(MSG_DEBUG, "WPS UPnP: Too many events queued for "
			   "subscriber %p", s);
		if (probereq)
			return 1;

		/* Drop oldest entry to allow EAP event to be stored. */
		e = event_dequeue(s);
		if (!e)
			return 1;
		event_delete(e);
	}

	if (s->last_event_failed && probereq && len > 0) {
		/*
		 * Avoid queuing frames for subscribers that may have left
		 * without unsubscribing.
		 */
		wpa_printf(MSG_DEBUG, "WPS UPnP: Do not queue more Probe "
			   "Request frames for subscription %p since last "
			   "delivery failed", s);
		return -1;
	}

	e = os_zalloc(sizeof(*e));
	if (e == NULL)
		return -1;
	dl_list_init(&e->list);
	e->s = s;
	e->data = wpabuf_dup(data);
	if (e->data == NULL) {
		os_free(e);
		return -1;
	}
	e->subscriber_sequence = s->next_subscriber_sequence++;
	if (s->next_subscriber_sequence == 0)
		s->next_subscriber_sequence++;
	wpa_printf(MSG_DEBUG, "WPS UPnP: Queue event %p for subscriber %p "
		   "(queue len %u)", e, s, len + 1);
	dl_list_add_tail(&s->event_queue, &e->list);
	event_send_all_later(s->sm);
	return 0;
}