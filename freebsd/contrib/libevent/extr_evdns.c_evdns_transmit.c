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
struct request {struct request* next; scalar_t__ transmit_me; } ;
struct evdns_base {int n_req_heads; struct request** req_heads; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int /*<<< orphan*/  evdns_request_transmit (struct request*) ; 

__attribute__((used)) static int
evdns_transmit(struct evdns_base *base) {
	char did_try_to_transmit = 0;
	int i;

	ASSERT_LOCKED(base);
	for (i = 0; i < base->n_req_heads; ++i) {
		if (base->req_heads[i]) {
			struct request *const started_at = base->req_heads[i], *req = started_at;
			/* first transmit all the requests which are currently waiting */
			do {
				if (req->transmit_me) {
					did_try_to_transmit = 1;
					evdns_request_transmit(req);
				}

				req = req->next;
			} while (req != started_at);
		}
	}

	return did_try_to_transmit;
}