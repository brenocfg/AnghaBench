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
struct evdns_server_port {scalar_t__ refcnt; int closing; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_server_port*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_server_port*) ; 
 int /*<<< orphan*/  server_port_free (struct evdns_server_port*) ; 

void
evdns_close_server_port(struct evdns_server_port *port)
{
	EVDNS_LOCK(port);
	if (--port->refcnt == 0) {
		EVDNS_UNLOCK(port);
		server_port_free(port);
	} else {
		port->closing = 1;
	}
}