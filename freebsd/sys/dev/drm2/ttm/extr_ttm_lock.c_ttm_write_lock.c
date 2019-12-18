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
struct ttm_lock {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int ERESTARTSYS ; 
 int PCATCH ; 
 int /*<<< orphan*/  TTM_WRITE_LOCK_PENDING ; 
 int /*<<< orphan*/  __ttm_write_lock (struct ttm_lock*) ; 
 int msleep (struct ttm_lock*,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ttm_lock*) ; 

int
ttm_write_lock(struct ttm_lock *lock, bool interruptible)
{
	const char *wmsg;
	int flags, ret;

	ret = 0;
	if (interruptible) {
		flags = PCATCH;
		wmsg = "ttmwi";
	} else {
		flags = 0;
		wmsg = "ttmw";
	}
	mtx_lock(&lock->lock);
	/* XXXKIB: linux uses __ttm_read_lock for uninterruptible sleeps */
	while (!__ttm_write_lock(lock)) {
		ret = -msleep(lock, &lock->lock, flags, wmsg, 0);
		if (ret == -EINTR || ret == -ERESTART)
			ret = -ERESTARTSYS;
		if (interruptible && ret != 0) {
			lock->flags &= ~TTM_WRITE_LOCK_PENDING;
			wakeup(lock);
			break;
		}
	}
	mtx_unlock(&lock->lock);

	return (ret);
}