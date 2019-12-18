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
struct request {struct nameserver* ns; } ;
struct nameserver {scalar_t__ requests_inflight; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 

__attribute__((used)) static void
request_swap_ns(struct request *req, struct nameserver *ns) {
	if (ns && req->ns != ns) {
		EVUTIL_ASSERT(req->ns->requests_inflight > 0);
		req->ns->requests_inflight--;
		ns->requests_inflight++;

		req->ns = ns;
	}
}