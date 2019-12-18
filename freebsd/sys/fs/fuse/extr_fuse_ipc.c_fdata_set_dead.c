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
struct fuse_data {int /*<<< orphan*/  ms_mtx; int /*<<< orphan*/  ticketer; int /*<<< orphan*/  ks_rsel; int /*<<< orphan*/  dataflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSESS_DEAD ; 
 int /*<<< orphan*/  FUSE_LOCK () ; 
 int /*<<< orphan*/  FUSE_UNLOCK () ; 
 scalar_t__ PZERO ; 
 scalar_t__ fdata_get_dead (struct fuse_data*) ; 
 int /*<<< orphan*/  fuse_lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_one (struct fuse_data*) ; 

void
fdata_set_dead(struct fuse_data *data)
{
	FUSE_LOCK();
	if (fdata_get_dead(data)) {
		FUSE_UNLOCK();
		return;
	}
	fuse_lck_mtx_lock(data->ms_mtx);
	data->dataflags |= FSESS_DEAD;
	wakeup_one(data);
	selwakeuppri(&data->ks_rsel, PZERO + 1);
	wakeup(&data->ticketer);
	fuse_lck_mtx_unlock(data->ms_mtx);
	FUSE_UNLOCK();
}