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
struct timeval {int member_1; int /*<<< orphan*/  member_0; } ;
struct event_config {int dummy; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BASE_FLAG_PRECISE_TIMER ; 
 int /*<<< orphan*/  EV_PERSIST ; 
 double MIN (int,int) ; 
 int TIMER_MAX_COST_USEC ; 
 scalar_t__ event_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new_with_config (struct event_config*) ; 
 int /*<<< orphan*/  event_config_free (struct event_config*) ; 
 struct event_config* event_config_new () ; 
 scalar_t__ event_config_set_flag (struct event_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_free (struct event*) ; 
 struct event* event_new (struct event_base*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_self_cbarg () ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  timer_bias_cb ; 
 int timer_bias_events ; 
 int timer_bias_spend ; 
 int /*<<< orphan*/  timer_bias_start ; 

__attribute__((used)) static double
timer_bias_calculate(void)
{
	struct event_config *cfg = NULL;
	struct event_base *base = NULL;
	struct event *timer = NULL;
	struct timeval tv = { 0, 1 };

	cfg = event_config_new();
	if (!cfg)
		goto err;
	if (event_config_set_flag(cfg, EVENT_BASE_FLAG_PRECISE_TIMER))
		goto err;
	base = event_base_new_with_config(cfg);
	if (!base)
		goto err;

	timer = event_new(base, -1, EV_PERSIST, timer_bias_cb, event_self_cbarg());
	if (!timer || event_add(timer, &tv)) {
		goto err;
	}

	evutil_gettimeofday(&timer_bias_start, NULL);
	event_base_dispatch(base);
	event_free(timer);

	return MIN(timer_bias_spend / 1e6 / timer_bias_events / TIMER_MAX_COST_USEC, 5);

err:
	if (cfg)
		event_config_free(cfg);
	if (timer)
		event_free(timer);
	if (base)
		event_base_free(base);

	fprintf(stderr, "Couldn't create event for CPU cycle counter bias\n");
	return -1;
}