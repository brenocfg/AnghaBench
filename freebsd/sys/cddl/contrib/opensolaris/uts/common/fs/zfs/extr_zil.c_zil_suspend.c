#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int zl_suspend; int /*<<< orphan*/  zl_lock; int /*<<< orphan*/  zl_cv_suspend; scalar_t__ zl_suspending; int /*<<< orphan*/  zl_dmu_pool; TYPE_2__* zl_header; } ;
typedef  TYPE_1__ zilog_t ;
struct TYPE_7__ {int zh_flags; int /*<<< orphan*/  zh_log; } ;
typedef  TYPE_2__ zil_header_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ BP_IS_HOLE (int /*<<< orphan*/ *) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EBUSY ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZIL_REPLAY_NEEDED ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dmu_objset_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_objset_zil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_long_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suspend_tag ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_commit_impl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_destroy (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  zil_resume (int /*<<< orphan*/ *) ; 

int
zil_suspend(const char *osname, void **cookiep)
{
	objset_t *os;
	zilog_t *zilog;
	const zil_header_t *zh;
	int error;

	error = dmu_objset_hold(osname, suspend_tag, &os);
	if (error != 0)
		return (error);
	zilog = dmu_objset_zil(os);

	mutex_enter(&zilog->zl_lock);
	zh = zilog->zl_header;

	if (zh->zh_flags & ZIL_REPLAY_NEEDED) {		/* unplayed log */
		mutex_exit(&zilog->zl_lock);
		dmu_objset_rele(os, suspend_tag);
		return (SET_ERROR(EBUSY));
	}

	/*
	 * Don't put a long hold in the cases where we can avoid it.  This
	 * is when there is no cookie so we are doing a suspend & resume
	 * (i.e. called from zil_vdev_offline()), and there's nothing to do
	 * for the suspend because it's already suspended, or there's no ZIL.
	 */
	if (cookiep == NULL && !zilog->zl_suspending &&
	    (zilog->zl_suspend > 0 || BP_IS_HOLE(&zh->zh_log))) {
		mutex_exit(&zilog->zl_lock);
		dmu_objset_rele(os, suspend_tag);
		return (0);
	}

	dsl_dataset_long_hold(dmu_objset_ds(os), suspend_tag);
	dsl_pool_rele(dmu_objset_pool(os), suspend_tag);

	zilog->zl_suspend++;

	if (zilog->zl_suspend > 1) {
		/*
		 * Someone else is already suspending it.
		 * Just wait for them to finish.
		 */

		while (zilog->zl_suspending)
			cv_wait(&zilog->zl_cv_suspend, &zilog->zl_lock);
		mutex_exit(&zilog->zl_lock);

		if (cookiep == NULL)
			zil_resume(os);
		else
			*cookiep = os;
		return (0);
	}

	/*
	 * If there is no pointer to an on-disk block, this ZIL must not
	 * be active (e.g. filesystem not mounted), so there's nothing
	 * to clean up.
	 */
	if (BP_IS_HOLE(&zh->zh_log)) {
		ASSERT(cookiep != NULL); /* fast path already handled */

		*cookiep = os;
		mutex_exit(&zilog->zl_lock);
		return (0);
	}

	zilog->zl_suspending = B_TRUE;
	mutex_exit(&zilog->zl_lock);

	/*
	 * We need to use zil_commit_impl to ensure we wait for all
	 * LWB_STATE_OPENED and LWB_STATE_ISSUED lwb's to be committed
	 * to disk before proceeding. If we used zil_commit instead, it
	 * would just call txg_wait_synced(), because zl_suspend is set.
	 * txg_wait_synced() doesn't wait for these lwb's to be
	 * LWB_STATE_FLUSH_DONE before returning.
	 */
	zil_commit_impl(zilog, 0);

	/*
	 * Now that we've ensured all lwb's are LWB_STATE_FLUSH_DONE, we
	 * use txg_wait_synced() to ensure the data from the zilog has
	 * migrated to the main pool before calling zil_destroy().
	 */
	txg_wait_synced(zilog->zl_dmu_pool, 0);

	zil_destroy(zilog, B_FALSE);

	mutex_enter(&zilog->zl_lock);
	zilog->zl_suspending = B_FALSE;
	cv_broadcast(&zilog->zl_cv_suspend);
	mutex_exit(&zilog->zl_lock);

	if (cookiep == NULL)
		zil_resume(os);
	else
		*cookiep = os;
	return (0);
}