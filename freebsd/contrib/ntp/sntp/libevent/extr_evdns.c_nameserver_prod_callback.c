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
struct nameserver {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nameserver_send_probe (struct nameserver* const) ; 

__attribute__((used)) static void
nameserver_prod_callback(evutil_socket_t fd, short events, void *arg) {
	struct nameserver *const ns = (struct nameserver *) arg;
	(void)fd;
	(void)events;

	EVDNS_LOCK(ns->base);
	nameserver_send_probe(ns);
	EVDNS_UNLOCK(ns->base);
}