#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct evdns_server_request {TYPE_1__** questions; int /*<<< orphan*/  nquestions; } ;
typedef  int ev_uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_ERR_REFUSED ; 
 int /*<<< orphan*/  evdns_server_request_add_a_reply (struct evdns_server_request*,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  evdns_server_request_respond (struct evdns_server_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gaic_server_cb(struct evdns_server_request *req, void *arg)
{
	ev_uint32_t answer = 0x7f000001;
	tt_assert(req->nquestions);
	evdns_server_request_add_a_reply(req, req->questions[0]->name, 1,
	    &answer, 100);
	evdns_server_request_respond(req, 0);
	return;
end:
	evdns_server_request_respond(req, DNS_ERR_REFUSED);
}