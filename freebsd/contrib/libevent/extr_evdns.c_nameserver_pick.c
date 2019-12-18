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
struct nameserver {struct nameserver* next; scalar_t__ state; } ;
struct evdns_base {scalar_t__ global_good_nameservers; struct nameserver* server_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 

__attribute__((used)) static struct nameserver *
nameserver_pick(struct evdns_base *base) {
	struct nameserver *started_at = base->server_head, *picked;
	ASSERT_LOCKED(base);
	if (!base->server_head) return NULL;

	/* if we don't have any good nameservers then there's no */
	/* point in trying to find one. */
	if (!base->global_good_nameservers) {
		base->server_head = base->server_head->next;
		return base->server_head;
	}

	/* remember that nameservers are in a circular list */
	for (;;) {
		if (base->server_head->state) {
			/* we think this server is currently good */
			picked = base->server_head;
			base->server_head = base->server_head->next;
			return picked;
		}

		base->server_head = base->server_head->next;
		if (base->server_head == started_at) {
			/* all the nameservers seem to be down */
			/* so we just return this one and hope for the */
			/* best */
			EVUTIL_ASSERT(base->global_good_nameservers == 0);
			picked = base->server_head;
			base->server_head = base->server_head->next;
			return picked;
		}
	}
}