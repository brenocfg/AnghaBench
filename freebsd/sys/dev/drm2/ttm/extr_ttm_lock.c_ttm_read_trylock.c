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
struct ttm_lock {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int ERESTART ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int PCATCH ; 
 int /*<<< orphan*/  __ttm_read_trylock (struct ttm_lock*,int*) ; 
 int msleep (struct ttm_lock*,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int ttm_read_trylock(struct ttm_lock *lock, bool interruptible)
{
	const char *wmsg;
	int flags, ret;
	bool locked;

	ret = 0;
	if (interruptible) {
		flags = PCATCH;
		wmsg = "ttmrti";
	} else {
		flags = 0;
		wmsg = "ttmrt";
	}
	mtx_lock(&lock->lock);
	while (!__ttm_read_trylock(lock, &locked)) {
		ret = -msleep(lock, &lock->lock, flags, wmsg, 0);
		if (ret == -EINTR || ret == -ERESTART)
			ret = -ERESTARTSYS;
		if (ret != 0)
			break;
	}
	MPASS(!locked || ret == 0);
	mtx_unlock(&lock->lock);

	return (locked) ? 0 : -EBUSY;
}