#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_timermgr_t ;
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  scalar_t__ isc_result_t ;
struct TYPE_8__ {int refs; int pertic; int /*<<< orphan*/  lock; int /*<<< orphan*/  shutdownevent; int /*<<< orphan*/ * timer; int /*<<< orphan*/ * task; int /*<<< orphan*/  pending; int /*<<< orphan*/  state; int /*<<< orphan*/  interval; int /*<<< orphan*/ * mctx; } ;
typedef  TYPE_1__ isc_ratelimiter_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
typedef  int /*<<< orphan*/  isc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_EVENT_INIT (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_RATELIMITEREVENT_SHUTDOWN ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  isc_interval_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* isc_mem_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_ratelimiter_idle ; 
 scalar_t__ isc_timer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_timertype_inactive ; 
 int /*<<< orphan*/  ratelimiter_shutdowncomplete ; 
 int /*<<< orphan*/  ratelimiter_tick ; 

isc_result_t
isc_ratelimiter_create(isc_mem_t *mctx, isc_timermgr_t *timermgr,
		       isc_task_t *task, isc_ratelimiter_t **ratelimiterp)
{
	isc_result_t result;
	isc_ratelimiter_t *rl;
	INSIST(ratelimiterp != NULL && *ratelimiterp == NULL);

	rl = isc_mem_get(mctx, sizeof(*rl));
	if (rl == NULL)
		return ISC_R_NOMEMORY;
	rl->mctx = mctx;
	rl->refs = 1;
	rl->task = task;
	isc_interval_set(&rl->interval, 0, 0);
	rl->timer = NULL;
	rl->pertic = 1;
	rl->state = isc_ratelimiter_idle;
	ISC_LIST_INIT(rl->pending);

	result = isc_mutex_init(&rl->lock);
	if (result != ISC_R_SUCCESS)
		goto free_mem;
	result = isc_timer_create(timermgr, isc_timertype_inactive,
				  NULL, NULL, rl->task, ratelimiter_tick,
				  rl, &rl->timer);
	if (result != ISC_R_SUCCESS)
		goto free_mutex;

	/*
	 * Increment the reference count to indicate that we may
	 * (soon) have events outstanding.
	 */
	rl->refs++;

	ISC_EVENT_INIT(&rl->shutdownevent,
		       sizeof(isc_event_t),
		       0, NULL, ISC_RATELIMITEREVENT_SHUTDOWN,
		       ratelimiter_shutdowncomplete, rl, rl, NULL, NULL);

	*ratelimiterp = rl;
	return (ISC_R_SUCCESS);

free_mutex:
	DESTROYLOCK(&rl->lock);
free_mem:
	isc_mem_put(mctx, rl, sizeof(*rl));
	return (result);
}