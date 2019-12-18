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
struct fuse_ticket {int /*<<< orphan*/  tk_aw_mtx; int /*<<< orphan*/  tk_aw_errno; } ;
struct fuse_data {int /*<<< orphan*/  ms_mtx; int /*<<< orphan*/  aw_mtx; int /*<<< orphan*/  ks_rsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  FUSE_ASSERT_AW_DONE (struct fuse_ticket*) ; 
 int /*<<< orphan*/  FUSE_LOCK () ; 
 int /*<<< orphan*/  FUSE_UNLOCK () ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  fdata_set_dead (struct fuse_data*) ; 
 int /*<<< orphan*/  fdata_trydestroy (struct fuse_data*) ; 
 int /*<<< orphan*/  fticket_set_answered (struct fuse_ticket*) ; 
 struct fuse_ticket* fuse_aw_pop (struct fuse_data*) ; 
 int /*<<< orphan*/  fuse_lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 struct fuse_ticket* fuse_ms_pop (struct fuse_data*) ; 
 int /*<<< orphan*/  fuse_ticket_drop (struct fuse_ticket*) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (struct fuse_ticket*) ; 

__attribute__((used)) static void
fdata_dtor(void *arg)
{
	struct fuse_data *fdata;
	struct fuse_ticket *tick;

	fdata = arg;
	if (fdata == NULL)
		return;

	fdata_set_dead(fdata);

	FUSE_LOCK();
	fuse_lck_mtx_lock(fdata->aw_mtx);
	/* wakup poll()ers */
	selwakeuppri(&fdata->ks_rsel, PZERO + 1);
	/* Don't let syscall handlers wait in vain */
	while ((tick = fuse_aw_pop(fdata))) {
		fuse_lck_mtx_lock(tick->tk_aw_mtx);
		fticket_set_answered(tick);
		tick->tk_aw_errno = ENOTCONN;
		wakeup(tick);
		fuse_lck_mtx_unlock(tick->tk_aw_mtx);
		FUSE_ASSERT_AW_DONE(tick);
		fuse_ticket_drop(tick);
	}
	fuse_lck_mtx_unlock(fdata->aw_mtx);

	/* Cleanup unsent operations */
	fuse_lck_mtx_lock(fdata->ms_mtx);
	while ((tick = fuse_ms_pop(fdata))) {
		fuse_ticket_drop(tick);
	}
	fuse_lck_mtx_unlock(fdata->ms_mtx);
	FUSE_UNLOCK();

	fdata_trydestroy(fdata);
}