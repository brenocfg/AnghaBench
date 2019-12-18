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
struct testcase_t {int flags; } ;
struct basic_test_data {int* pair; scalar_t__ base; } ;

/* Variables and functions */
 int TT_FORK ; 
 int TT_NEED_BASE ; 
 int TT_NEED_DNS ; 
 int TT_NEED_SOCKETPAIR ; 
 int TT_NO_LOGS ; 
 int /*<<< orphan*/  evdns_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_assert_ok_ (scalar_t__) ; 
 int /*<<< orphan*/  event_base_free (scalar_t__) ; 
 int /*<<< orphan*/  event_set_log_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_closesocket (int) ; 
 int /*<<< orphan*/  free (struct basic_test_data*) ; 
 int /*<<< orphan*/  libevent_global_shutdown () ; 

int
basic_test_cleanup(const struct testcase_t *testcase, void *ptr)
{
	struct basic_test_data *data = ptr;

	if (testcase->flags & TT_NO_LOGS)
		event_set_log_callback(NULL);

	if (testcase->flags & TT_NEED_SOCKETPAIR) {
		if (data->pair[0] != -1)
			evutil_closesocket(data->pair[0]);
		if (data->pair[1] != -1)
			evutil_closesocket(data->pair[1]);
	}

	if (testcase->flags & TT_NEED_DNS) {
		evdns_shutdown(0);
	}

	if (testcase->flags & TT_NEED_BASE) {
		if (data->base) {
			event_base_assert_ok_(data->base);
			event_base_free(data->base);
		}
	}

	if (testcase->flags & TT_FORK)
		libevent_global_shutdown();

	free(data);

	return 1;
}