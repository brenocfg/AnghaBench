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
struct turnstile_chain {int /*<<< orphan*/  tc_lock; } ;
struct turnstile {int /*<<< orphan*/ * ts_lockobj; int /*<<< orphan*/  ts_lock; } ;
struct lock_object {int dummy; } ;
struct TYPE_2__ {struct turnstile* td_turnstile; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct turnstile_chain* TC_LOOKUP (struct lock_object*) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

void
turnstile_unlock(struct turnstile *ts, struct lock_object *lock)
{
	struct turnstile_chain *tc;

	mtx_assert(&ts->ts_lock, MA_OWNED);
	mtx_unlock_spin(&ts->ts_lock);
	if (ts == curthread->td_turnstile)
		ts->ts_lockobj = NULL;
	tc = TC_LOOKUP(lock);
	mtx_unlock_spin(&tc->tc_lock);
}