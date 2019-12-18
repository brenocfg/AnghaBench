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
struct nameserver {int /*<<< orphan*/  base; scalar_t__ choked; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (int /*<<< orphan*/ ) ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  evdns_transmit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nameserver_read (struct nameserver*) ; 
 int /*<<< orphan*/  nameserver_write_waiting (struct nameserver*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nameserver_ready_callback(evutil_socket_t fd, short events, void *arg) {
	struct nameserver *ns = (struct nameserver *) arg;
	(void)fd;

	EVDNS_LOCK(ns->base);
	if (events & EV_WRITE) {
		ns->choked = 0;
		if (!evdns_transmit(ns->base)) {
			nameserver_write_waiting(ns, 0);
		}
	}
	if (events & EV_READ) {
		nameserver_read(ns);
	}
	EVDNS_UNLOCK(ns->base);
}