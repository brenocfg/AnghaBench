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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct evwatch {int dummy; } ;
struct event_base {int dummy; } ;
struct basic_test_data {struct event_base* base; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  check_callback_1 ; 
 int /*<<< orphan*/  check_callback_2 ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_once (struct event_base*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timeval*) ; 
 struct evwatch* evwatch_check_new (struct event_base*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evwatch_free (struct evwatch*) ; 
 struct evwatch* evwatch_prepare_new (struct event_base*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iteration ; 
 int /*<<< orphan*/  prepare_callback_1 ; 
 int /*<<< orphan*/  prepare_callback_2 ; 
 TYPE_1__ start_time ; 
 int /*<<< orphan*/  timeout_callback ; 
 int /*<<< orphan*/  user_arg ; 

__attribute__((used)) static void
test_callback_ordering(void *ptr)
{
	struct basic_test_data *data = ptr;
	struct event_base *base = data->base;
	struct evwatch *prepare_callback_2_watcher;
	struct evwatch *check_callback_2_watcher;
	struct timeval timeout;

	/* install prepare and check watchers */
	evwatch_prepare_new(base, &prepare_callback_1, &user_arg);
	evwatch_check_new(base, &check_callback_1, &user_arg);
	prepare_callback_2_watcher = evwatch_prepare_new(base, &prepare_callback_2, &user_arg);
	check_callback_2_watcher = evwatch_check_new(base, &check_callback_2, &user_arg);

	/* schedule an 1 second timeout event, and run the event loop until the
	 * timeout fires */
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	event_base_once(base, -1, EV_TIMEOUT, &timeout_callback, 0, &timeout);
	event_base_dispatch(base);

	/* second iteration: free two of the watchers, schedule a timeout and
	 * run the event loop again */
	iteration = 1;
	start_time.tv_sec = 0;
	evwatch_free(prepare_callback_2_watcher);
	evwatch_free(check_callback_2_watcher);
	event_base_once(base, -1, EV_TIMEOUT, &timeout_callback, 0, &timeout);
	event_base_dispatch(base);
}