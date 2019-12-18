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
typedef  int /*<<< orphan*/  u32 ;
struct evdns_server_request {int nquestions; TYPE_1__** questions; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ dns_question_class; char* name; } ;

/* Variables and functions */
 scalar_t__ EVDNS_CLASS_INET ; 
 scalar_t__ EVDNS_TYPE_A ; 
 scalar_t__ EVDNS_TYPE_PTR ; 
 int evdns_server_request_add_a_reply (struct evdns_server_request*,char*,int,int /*<<< orphan*/ *,int) ; 
 int evdns_server_request_add_ptr_reply (struct evdns_server_request*,int /*<<< orphan*/ *,char*,char*,int) ; 
 int evdns_server_request_respond (struct evdns_server_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
evdns_server_callback(struct evdns_server_request *req, void *data)
{
	int i, r;
	(void)data;
	/* dummy; give 192.168.11.11 as an answer for all A questions,
	 *	give foo.bar.example.com as an answer for all PTR questions. */
	for (i = 0; i < req->nquestions; ++i) {
		u32 ans = htonl(0xc0a80b0bUL);
		if (req->questions[i]->type == EVDNS_TYPE_A &&
		    req->questions[i]->dns_question_class == EVDNS_CLASS_INET) {
			printf(" -- replying for %s (A)\n", req->questions[i]->name);
			r = evdns_server_request_add_a_reply(req, req->questions[i]->name,
										  1, &ans, 10);
			if (r<0)
				printf("eeep, didn't work.\n");
		} else if (req->questions[i]->type == EVDNS_TYPE_PTR &&
		    req->questions[i]->dns_question_class == EVDNS_CLASS_INET) {
			printf(" -- replying for %s (PTR)\n", req->questions[i]->name);
			r = evdns_server_request_add_ptr_reply(req, NULL, req->questions[i]->name,
											"foo.bar.example.com", 10);
			if (r<0)
				printf("ugh, no luck");
		} else {
			printf(" -- skipping %s [%d %d]\n", req->questions[i]->name,
				   req->questions[i]->type, req->questions[i]->dns_question_class);
		}
	}

	r = evdns_server_request_respond(req, 0);
	if (r<0)
		printf("eeek, couldn't send reply.\n");
}