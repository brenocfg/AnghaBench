#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int zl_stop_sync; int /*<<< orphan*/  zl_cv_suspend; int /*<<< orphan*/  zl_lock; int /*<<< orphan*/  zl_issuer_lock; TYPE_1__* zl_itxg; int /*<<< orphan*/  zl_itx_commit_list; int /*<<< orphan*/  zl_lwb_list; int /*<<< orphan*/  zl_suspending; int /*<<< orphan*/  zl_suspend; } ;
typedef  TYPE_2__ zilog_t ;
struct TYPE_5__ {int /*<<< orphan*/  itxg_lock; scalar_t__ itxg_itxs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_itxg_clean (scalar_t__) ; 

void
zil_free(zilog_t *zilog)
{
	zilog->zl_stop_sync = 1;

	ASSERT0(zilog->zl_suspend);
	ASSERT0(zilog->zl_suspending);

	ASSERT(list_is_empty(&zilog->zl_lwb_list));
	list_destroy(&zilog->zl_lwb_list);

	ASSERT(list_is_empty(&zilog->zl_itx_commit_list));
	list_destroy(&zilog->zl_itx_commit_list);

	for (int i = 0; i < TXG_SIZE; i++) {
		/*
		 * It's possible for an itx to be generated that doesn't dirty
		 * a txg (e.g. ztest TX_TRUNCATE). So there's no zil_clean()
		 * callback to remove the entry. We remove those here.
		 *
		 * Also free up the ziltest itxs.
		 */
		if (zilog->zl_itxg[i].itxg_itxs)
			zil_itxg_clean(zilog->zl_itxg[i].itxg_itxs);
		mutex_destroy(&zilog->zl_itxg[i].itxg_lock);
	}

	mutex_destroy(&zilog->zl_issuer_lock);
	mutex_destroy(&zilog->zl_lock);

	cv_destroy(&zilog->zl_cv_suspend);

	kmem_free(zilog, sizeof (zilog_t));
}