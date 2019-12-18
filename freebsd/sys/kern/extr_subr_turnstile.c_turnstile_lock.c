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
struct turnstile_chain {int /*<<< orphan*/  tc_lock; } ;
struct turnstile {struct thread* ts_owner; int /*<<< orphan*/  ts_lock; struct lock_object* ts_lockobj; } ;
struct thread {int dummy; } ;
struct lock_object {int dummy; } ;

/* Variables and functions */
 struct turnstile_chain* TC_LOOKUP (struct lock_object*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

bool
turnstile_lock(struct turnstile *ts, struct lock_object **lockp,
    struct thread **tdp)
{
	struct turnstile_chain *tc;
	struct lock_object *lock;

	if ((lock = ts->ts_lockobj) == NULL)
		return (false);
	tc = TC_LOOKUP(lock);
	mtx_lock_spin(&tc->tc_lock);
	mtx_lock_spin(&ts->ts_lock);
	if (__predict_false(lock != ts->ts_lockobj)) {
		mtx_unlock_spin(&tc->tc_lock);
		mtx_unlock_spin(&ts->ts_lock);
		return (false);
	}
	*lockp = lock;
	*tdp = ts->ts_owner;
	return (true);
}