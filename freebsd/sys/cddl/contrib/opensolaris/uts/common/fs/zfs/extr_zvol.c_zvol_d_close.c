#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int zv_flags; int zv_total_opens; int /*<<< orphan*/  zv_sync_cnt; } ;
typedef  TYPE_1__ zvol_state_t ;
struct thread {int dummy; } ;
struct cdev {TYPE_1__* si_drv2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int FDSYNC ; 
 int FSYNC ; 
 int ZVOL_EXCL ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 
 int /*<<< orphan*/  zvol_last_close (TYPE_1__*) ; 

__attribute__((used)) static int
zvol_d_close(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	zvol_state_t *zv = dev->si_drv2;

	mutex_enter(&zfsdev_state_lock);
	if (zv->zv_flags & ZVOL_EXCL) {
		ASSERT(zv->zv_total_opens == 1);
		zv->zv_flags &= ~ZVOL_EXCL;
	}

	/*
	 * If the open count is zero, this is a spurious close.
	 * That indicates a bug in the kernel / DDI framework.
	 */
	ASSERT(zv->zv_total_opens != 0);

	/*
	 * You may get multiple opens, but only one close.
	 */
	zv->zv_total_opens--;
	if (flags & (FSYNC | FDSYNC))
		zv->zv_sync_cnt--;

	if (zv->zv_total_opens == 0)
		zvol_last_close(zv);

	mutex_exit(&zfsdev_state_lock);
	return (0);
}