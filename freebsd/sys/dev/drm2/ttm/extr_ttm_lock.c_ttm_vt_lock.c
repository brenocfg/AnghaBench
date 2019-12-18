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
struct ttm_object_file {int dummy; } ;
struct ttm_lock {struct ttm_object_file* vt_holder; int /*<<< orphan*/  base; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int ERESTARTSYS ; 
 int PCATCH ; 
 int /*<<< orphan*/  TTM_VT_LOCK_PENDING ; 
 int /*<<< orphan*/  __ttm_vt_lock (struct ttm_lock*) ; 
 int /*<<< orphan*/  __ttm_vt_unlock (struct ttm_lock*) ; 
 int msleep (struct ttm_lock*,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int ttm_base_object_init (struct ttm_object_file*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_lock_type ; 
 int /*<<< orphan*/  ttm_vt_lock_remove ; 
 int /*<<< orphan*/  wakeup (struct ttm_lock*) ; 

int ttm_vt_lock(struct ttm_lock *lock,
		bool interruptible,
		struct ttm_object_file *tfile)
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
	while (!__ttm_vt_lock(lock)) {
		ret = -msleep(lock, &lock->lock, flags, wmsg, 0);
		if (ret == -EINTR || ret == -ERESTART)
			ret = -ERESTARTSYS;
		if (interruptible && ret != 0) {
			lock->flags &= ~TTM_VT_LOCK_PENDING;
			wakeup(lock);
			break;
		}
	}

	/*
	 * Add a base-object, the destructor of which will
	 * make sure the lock is released if the client dies
	 * while holding it.
	 */

	ret = ttm_base_object_init(tfile, &lock->base, false,
				   ttm_lock_type, &ttm_vt_lock_remove, NULL);
	if (ret)
		(void)__ttm_vt_unlock(lock);
	else
		lock->vt_holder = tfile;

	return (ret);
}