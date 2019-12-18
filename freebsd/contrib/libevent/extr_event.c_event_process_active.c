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
struct timeval {int dummy; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct event_base {int max_dispatch_callbacks; int limit_callbacks_after_prio; int nactivequeues; int event_running_priority; struct evcallback_list* activequeues; TYPE_1__ max_dispatch_time; } ;
struct evcallback_list {int dummy; } ;

/* Variables and functions */
 int const INT_MAX ; 
 int /*<<< orphan*/ * TAILQ_FIRST (struct evcallback_list*) ; 
 int event_process_active_single_queue (struct event_base*,struct evcallback_list*,int const,struct timeval const*) ; 
 int /*<<< orphan*/  evutil_timeradd (TYPE_1__*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  gettime (struct event_base*,struct timeval*) ; 
 int /*<<< orphan*/  update_time_cache (struct event_base*) ; 

__attribute__((used)) static int
event_process_active(struct event_base *base)
{
	/* Caller must hold th_base_lock */
	struct evcallback_list *activeq = NULL;
	int i, c = 0;
	const struct timeval *endtime;
	struct timeval tv;
	const int maxcb = base->max_dispatch_callbacks;
	const int limit_after_prio = base->limit_callbacks_after_prio;
	if (base->max_dispatch_time.tv_sec >= 0) {
		update_time_cache(base);
		gettime(base, &tv);
		evutil_timeradd(&base->max_dispatch_time, &tv, &tv);
		endtime = &tv;
	} else {
		endtime = NULL;
	}

	for (i = 0; i < base->nactivequeues; ++i) {
		if (TAILQ_FIRST(&base->activequeues[i]) != NULL) {
			base->event_running_priority = i;
			activeq = &base->activequeues[i];
			if (i < limit_after_prio)
				c = event_process_active_single_queue(base, activeq,
				    INT_MAX, NULL);
			else
				c = event_process_active_single_queue(base, activeq,
				    maxcb, endtime);
			if (c < 0) {
				goto done;
			} else if (c > 0)
				break; /* Processed a real event; do not
					* consider lower-priority events */
			/* If we get here, all of the events we processed
			 * were internal.  Continue. */
		}
	}

done:
	base->event_running_priority = -1;

	return c;
}