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
struct http_newreqcb_test_state {int connections_noticed; int /*<<< orphan*/  connections_throttled; } ;
struct evhttp_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_newreqcb_test_state_check (struct http_newreqcb_test_state*) ; 

__attribute__((used)) static int
http_newreqcb(struct evhttp_request* req, void *arg)
{
	struct http_newreqcb_test_state* state = arg;
	++state->connections_noticed;
	http_newreqcb_test_state_check(state);
	if (1 == state->connections_noticed % 7) {
		state->connections_throttled++;
		return -1;
	}
	return 0;
}