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
struct pthread_mutex {int /*<<< orphan*/  m_flags; } ;
struct pthread {scalar_t__ nwaiter_defer; TYPE_1__* wake_addr; int /*<<< orphan*/ ** defer_waiters; struct pthread_mutex* mutex_obj; } ;
struct broadcast_arg {scalar_t__ count; int /*<<< orphan*/ ** waddrs; struct pthread* curthread; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ MAX_DEFER_WAITERS ; 
 int /*<<< orphan*/  PMUTEX_FLAG_DEFERRED ; 
 scalar_t__ PMUTEX_OWNER_ID (struct pthread_mutex*) ; 
 scalar_t__ TID (struct pthread*) ; 
 int /*<<< orphan*/  _thr_wake_all (int /*<<< orphan*/ **,scalar_t__) ; 

__attribute__((used)) static void
drop_cb(struct pthread *td, void *arg)
{
	struct broadcast_arg *ba = arg;
	struct pthread_mutex *mp;
	struct pthread *curthread = ba->curthread;

	mp = td->mutex_obj;
	if (PMUTEX_OWNER_ID(mp) == TID(curthread)) {
		if (curthread->nwaiter_defer >= MAX_DEFER_WAITERS) {
			_thr_wake_all(curthread->defer_waiters,
			    curthread->nwaiter_defer);
			curthread->nwaiter_defer = 0;
		}
		curthread->defer_waiters[curthread->nwaiter_defer++] =
		    &td->wake_addr->value;
		mp->m_flags |= PMUTEX_FLAG_DEFERRED;
	} else {
		if (ba->count >= MAX_DEFER_WAITERS) {
			_thr_wake_all(ba->waddrs, ba->count);
			ba->count = 0;
		}
		ba->waddrs[ba->count++] = &td->wake_addr->value;
	}
}