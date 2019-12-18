#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zv_total_opens; int zv_flags; int zv_sync_cnt; int /*<<< orphan*/  zv_zilog; } ;
typedef  TYPE_1__ zvol_state_t ;
struct thread {int dummy; } ;
struct cdev {TYPE_1__* si_drv2; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EROFS ; 
 int FDSYNC ; 
 int FEXCL ; 
 int FSYNC ; 
 int FWRITE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZVOL_EXCL ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int ZVOL_RDONLY ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 
 int /*<<< orphan*/  zil_async_to_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zvol_first_open (TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_last_close (TYPE_1__*) ; 

__attribute__((used)) static int
zvol_d_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	zvol_state_t *zv = dev->si_drv2;
	int err = 0;

	mutex_enter(&zfsdev_state_lock);
	if (zv->zv_total_opens == 0)
		err = zvol_first_open(zv);
	if (err) {
		mutex_exit(&zfsdev_state_lock);
		return (err);
	}
	if ((flags & FWRITE) && (zv->zv_flags & ZVOL_RDONLY)) {
		err = SET_ERROR(EROFS);
		goto out;
	}
	if (zv->zv_flags & ZVOL_EXCL) {
		err = SET_ERROR(EBUSY);
		goto out;
	}
#ifdef FEXCL
	if (flags & FEXCL) {
		if (zv->zv_total_opens != 0) {
			err = SET_ERROR(EBUSY);
			goto out;
		}
		zv->zv_flags |= ZVOL_EXCL;
	}
#endif

	zv->zv_total_opens++;
	if (flags & (FSYNC | FDSYNC)) {
		zv->zv_sync_cnt++;
		if (zv->zv_sync_cnt == 1)
			zil_async_to_sync(zv->zv_zilog, ZVOL_OBJ);
	}
	mutex_exit(&zfsdev_state_lock);
	return (err);
out:
	if (zv->zv_total_opens == 0)
		zvol_last_close(zv);
	mutex_exit(&zfsdev_state_lock);
	return (err);
}