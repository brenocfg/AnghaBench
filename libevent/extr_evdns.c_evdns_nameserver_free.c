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
struct nameserver {scalar_t__ socket; scalar_t__ state; int /*<<< orphan*/  timeout_event; int /*<<< orphan*/ * probe_request; int /*<<< orphan*/  base; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  evdns_cancel_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_debug_unassign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 int /*<<< orphan*/  mm_free (struct nameserver*) ; 

__attribute__((used)) static void
evdns_nameserver_free(struct nameserver *server)
{
	if (server->socket >= 0)
		evutil_closesocket(server->socket);
	(void) event_del(&server->event);
	event_debug_unassign(&server->event);
	if (server->state == 0)
		(void) event_del(&server->timeout_event);
	if (server->probe_request) {
		evdns_cancel_request(server->base, server->probe_request);
		server->probe_request = NULL;
	}
	event_debug_unassign(&server->timeout_event);
	mm_free(server);
}