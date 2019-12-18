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
typedef  struct nameserver {struct nameserver const* next; } const nameserver ;
struct evdns_base {struct nameserver const* server_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 

int
evdns_base_count_nameservers(struct evdns_base *base)
{
	const struct nameserver *server;
	int n = 0;

	EVDNS_LOCK(base);
	server = base->server_head;
	if (!server)
		goto done;
	do {
		++n;
		server = server->next;
	} while (server != base->server_head);
done:
	EVDNS_UNLOCK(base);
	return n;
}