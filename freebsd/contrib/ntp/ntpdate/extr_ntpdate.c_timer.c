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
struct server {scalar_t__ event_time; struct server* next_server; } ;

/* Variables and functions */
 scalar_t__ current_time ; 
 struct server* sys_servers ; 
 int /*<<< orphan*/  transmit (struct server*) ; 

void
timer(void)
{
	struct server *server;

	/*
	 * Bump the current idea of the time
	 */
	current_time++;

	/*
	 * Search through the server list looking for guys
	 * who's event timers have expired.  Give these to
	 * the transmit routine.
	 */
	for (server = sys_servers; server != NULL;
	     server = server->next_server) {
		if (server->event_time != 0
		    && server->event_time <= current_time)
			transmit(server);
	}
}