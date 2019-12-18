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
typedef  int /*<<< orphan*/  u16 ;
struct request {struct request* next; int /*<<< orphan*/  trans_id; } ;
struct evdns_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 struct request* REQ_HEAD (struct evdns_base*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request *
request_find_from_trans_id(struct evdns_base *base, u16 trans_id) {
	struct request *req = REQ_HEAD(base, trans_id);
	struct request *const started_at = req;

	ASSERT_LOCKED(base);

	if (req) {
		do {
			if (req->trans_id == trans_id) return req;
			req = req->next;
		} while (req != started_at);
	}

	return NULL;
}