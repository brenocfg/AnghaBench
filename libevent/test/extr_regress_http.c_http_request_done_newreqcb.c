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
struct http_newreqcb_test_state {int /*<<< orphan*/  connections_done; int /*<<< orphan*/  connections_good; } ;
struct evhttp_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ HTTP_OK ; 
 scalar_t__ evhttp_request_get_response_code (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_request_set_error_cb (struct evhttp_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_newreqcb_test_state_check (struct http_newreqcb_test_state*) ; 

__attribute__((used)) static void
http_request_done_newreqcb(struct evhttp_request *req, void *arg)
{
	struct http_newreqcb_test_state* state = arg;
	if (req && evhttp_request_get_response_code(req) == HTTP_OK) {
		++state->connections_good;
		evhttp_request_set_error_cb(req, NULL);
	}
	++state->connections_done;

	http_newreqcb_test_state_check(state);
}