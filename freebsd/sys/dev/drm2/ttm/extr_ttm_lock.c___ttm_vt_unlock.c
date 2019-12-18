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
struct ttm_lock {int flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int TTM_VT_LOCK ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wakeup (struct ttm_lock*) ; 

__attribute__((used)) static int __ttm_vt_unlock(struct ttm_lock *lock)
{
	int ret = 0;

	mtx_lock(&lock->lock);
	if (unlikely(!(lock->flags & TTM_VT_LOCK)))
		ret = -EINVAL;
	lock->flags &= ~TTM_VT_LOCK;
	wakeup(lock);
	mtx_unlock(&lock->lock);

	return ret;
}