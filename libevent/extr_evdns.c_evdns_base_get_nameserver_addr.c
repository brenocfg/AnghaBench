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
struct sockaddr {int dummy; } ;
struct nameserver {scalar_t__ addrlen; int /*<<< orphan*/  address; struct nameserver* next; } ;
struct evdns_base {struct nameserver* server_head; } ;
typedef  scalar_t__ ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ *,scalar_t__) ; 

int
evdns_base_get_nameserver_addr(struct evdns_base *base, int idx,
    struct sockaddr *sa, ev_socklen_t len)
{
	int result = -1;
	int i;
	struct nameserver *server;
	EVDNS_LOCK(base);
	server = base->server_head;
	for (i = 0; i < idx && server; ++i, server = server->next) {
		if (server->next == base->server_head)
			goto done;
	}
	if (! server)
		goto done;

	if (server->addrlen > len) {
		result = (int) server->addrlen;
		goto done;
	}

	memcpy(sa, &server->address, server->addrlen);
	result = (int) server->addrlen;
done:
	EVDNS_UNLOCK(base);
	return result;
}