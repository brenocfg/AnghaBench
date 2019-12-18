#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zl_itx_commit_list; int /*<<< orphan*/  zl_lock; TYPE_2__* zl_last_lwb_opened; int /*<<< orphan*/  zl_issuer_lock; } ;
typedef  TYPE_1__ zilog_t ;
struct TYPE_11__ {scalar_t__ lwb_state; } ;
typedef  TYPE_2__ lwb_t ;
struct TYPE_12__ {scalar_t__ lrc_txtype; } ;
typedef  TYPE_3__ lr_t ;
struct TYPE_13__ {TYPE_3__ itx_lr; int /*<<< orphan*/ * itx_private; } ;
typedef  TYPE_4__ itx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMPLY (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LWB_STATE_FLUSH_DONE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ TX_COMMIT ; 
 TYPE_4__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_commit_waiter_link_lwb (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zil_commit_waiter_skip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_itx_destroy (TYPE_4__*) ; 

__attribute__((used)) static void
zil_prune_commit_list(zilog_t *zilog)
{
	itx_t *itx;

	ASSERT(MUTEX_HELD(&zilog->zl_issuer_lock));

	while (itx = list_head(&zilog->zl_itx_commit_list)) {
		lr_t *lrc = &itx->itx_lr;
		if (lrc->lrc_txtype != TX_COMMIT)
			break;

		mutex_enter(&zilog->zl_lock);

		lwb_t *last_lwb = zilog->zl_last_lwb_opened;
		if (last_lwb == NULL ||
		    last_lwb->lwb_state == LWB_STATE_FLUSH_DONE) {
			/*
			 * All of the itxs this waiter was waiting on
			 * must have already completed (or there were
			 * never any itx's for it to wait on), so it's
			 * safe to skip this waiter and mark it done.
			 */
			zil_commit_waiter_skip(itx->itx_private);
		} else {
			zil_commit_waiter_link_lwb(itx->itx_private, last_lwb);
			itx->itx_private = NULL;
		}

		mutex_exit(&zilog->zl_lock);

		list_remove(&zilog->zl_itx_commit_list, itx);
		zil_itx_destroy(itx);
	}

	IMPLY(itx != NULL, itx->itx_lr.lrc_txtype != TX_COMMIT);
}