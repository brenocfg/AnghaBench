#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct alerted_record {int timed_out; int /*<<< orphan*/  alerted_at; TYPE_1__* cond; TYPE_2__ delay; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;
typedef  int /*<<< orphan*/  THREAD_FN ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOCK_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVLOCK_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVTHREAD_COND_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVTHREAD_COND_WAIT_TIMED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  THREAD_RETURN () ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static THREAD_FN
wait_for_condition(void *arg)
{
	struct alerted_record *rec = arg;
	int r;

	EVLOCK_LOCK(rec->cond->lock, 0);
	if (rec->delay.tv_sec || rec->delay.tv_usec) {
		r = EVTHREAD_COND_WAIT_TIMED(rec->cond->cond, rec->cond->lock,
		    &rec->delay);
	} else {
		r = EVTHREAD_COND_WAIT(rec->cond->cond, rec->cond->lock);
	}
	EVLOCK_UNLOCK(rec->cond->lock, 0);

	evutil_gettimeofday(&rec->alerted_at, NULL);
	if (r == 1)
		rec->timed_out = 1;

	THREAD_RETURN();
}