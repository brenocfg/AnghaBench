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
struct upnp_pending_message {int /*<<< orphan*/  msg; struct upnp_pending_message* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct upnp_pending_message*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void wps_free_pending_msgs(struct upnp_pending_message *msgs)
{
	struct upnp_pending_message *p, *prev;
	p = msgs;
	while (p) {
		prev = p;
		p = p->next;
		wpabuf_free(prev->msg);
		os_free(prev);
	}
}