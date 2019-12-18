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
struct evdns_server_request {int nquestions; TYPE_1__** questions; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  TT_DIE (char*) ; 
 int /*<<< orphan*/  current_req ; 
 int /*<<< orphan*/  evdns_cancel_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdns_server_request_respond (struct evdns_server_request*,int) ; 
 scalar_t__ request_count ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
search_cancel_server_cb(struct evdns_server_request *req, void *data)
{
	const char *question;

	if (req->nquestions != 1)
		TT_DIE(("Only handling one question at a time; got %d",
			req->nquestions));

	question = req->questions[0]->name;

	TT_BLATHER(("got question, %s", question));

	tt_assert(request_count > 0);
	tt_assert(!evdns_server_request_respond(req, 3));

	if (!--request_count)
		evdns_cancel_request(NULL, current_req);

end:
	;
}