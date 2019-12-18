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
struct timeval {int member_0; int tv_sec; scalar_t__ tv_usec; int /*<<< orphan*/  member_1; } ;
struct event_config {int dummy; } ;
struct event_base {int dummy; } ;
struct TYPE_2__ {struct event_base* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int QUEUE_THREAD_COUNT ; 
 int /*<<< orphan*/  THREAD_JOIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  callback_count ; 
 TYPE_1__* deferred_data ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new_with_config (struct event_config*) ; 
 int /*<<< orphan*/  event_base_once (struct event_base*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  event_config_free (struct event_config*) ; 
 struct event_config* event_config_new () ; 
 int /*<<< orphan*/  event_config_set_max_dispatch_interval (struct event_config*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timersub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/ * load_threads ; 
 int /*<<< orphan*/  start_threads_callback ; 
 int /*<<< orphan*/  timer_callback ; 
 int /*<<< orphan*/  timer_end ; 
 int /*<<< orphan*/  timer_start ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
thread_deferred_cb_skew(void *arg)
{
	struct timeval tv_timer = {1, 0};
	struct event_base *base = NULL;
	struct event_config *cfg = NULL;
	struct timeval elapsed;
	int elapsed_usec;
	int i;

	cfg = event_config_new();
	tt_assert(cfg);
	event_config_set_max_dispatch_interval(cfg, NULL, 16, 0);

	base = event_base_new_with_config(cfg);
	tt_assert(base);

	for (i = 0; i < QUEUE_THREAD_COUNT; ++i)
		deferred_data[i].queue = base;

	evutil_gettimeofday(&timer_start, NULL);
	event_base_once(base, -1, EV_TIMEOUT, timer_callback, NULL,
			&tv_timer);
	event_base_once(base, -1, EV_TIMEOUT, start_threads_callback,
			NULL, NULL);
	event_base_dispatch(base);

	evutil_timersub(&timer_end, &timer_start, &elapsed);
	TT_BLATHER(("callback count, %u", callback_count));
	elapsed_usec =
	    (unsigned)(elapsed.tv_sec*1000000 + elapsed.tv_usec);
	TT_BLATHER(("elapsed time, %u usec", elapsed_usec));

	/* XXX be more intelligent here.  just make sure skew is
	 * within .4 seconds for now. */
	tt_assert(elapsed_usec >= 600000 && elapsed_usec <= 1400000);

end:
	for (i = 0; i < QUEUE_THREAD_COUNT; ++i)
		THREAD_JOIN(load_threads[i]);
	if (base)
		event_base_free(base);
	if (cfg)
		event_config_free(cfg);
}