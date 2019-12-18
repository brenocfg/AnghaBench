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
struct http_newreqcb_test_state {int /*<<< orphan*/  connections_error; } ;
typedef  enum evhttp_request_error { ____Placeholder_evhttp_request_error } evhttp_request_error ;

/* Variables and functions */
 int /*<<< orphan*/  http_newreqcb_test_state_check (struct http_newreqcb_test_state*) ; 

__attribute__((used)) static void
http_request_error_newreqcb(enum evhttp_request_error err, void *arg)
{
	struct http_newreqcb_test_state* state = arg;
	++state->connections_error;

	http_newreqcb_test_state_check(state);
}