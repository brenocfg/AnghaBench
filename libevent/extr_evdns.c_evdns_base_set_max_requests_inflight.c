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
struct request {int trans_id; } ;
struct evdns_base {int n_req_heads; int global_max_requests_inflight; struct request** req_heads; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  evdns_request_insert (struct request*,struct request**) ; 
 int /*<<< orphan*/  evdns_request_remove (struct request*,struct request**) ; 
 struct request** mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct request**) ; 

__attribute__((used)) static int
evdns_base_set_max_requests_inflight(struct evdns_base *base, int maxinflight)
{
	int old_n_heads = base->n_req_heads, n_heads;
	struct request **old_heads = base->req_heads, **new_heads, *req;
	int i;

	ASSERT_LOCKED(base);
	if (maxinflight < 1)
		maxinflight = 1;
	n_heads = (maxinflight+4) / 5;
	EVUTIL_ASSERT(n_heads > 0);
	new_heads = mm_calloc(n_heads, sizeof(struct request*));
	if (!new_heads)
		return (-1);
	if (old_heads) {
		for (i = 0; i < old_n_heads; ++i) {
			while (old_heads[i]) {
				req = old_heads[i];
				evdns_request_remove(req, &old_heads[i]);
				evdns_request_insert(req, &new_heads[req->trans_id % n_heads]);
			}
		}
		mm_free(old_heads);
	}
	base->req_heads = new_heads;
	base->n_req_heads = n_heads;
	base->global_max_requests_inflight = maxinflight;
	return (0);
}