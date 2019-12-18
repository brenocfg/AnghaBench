#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  zl_spa; } ;
typedef  TYPE_1__ zilog_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_14__ {scalar_t__ blk_birth; } ;
struct TYPE_12__ {TYPE_4__ lr_blkptr; } ;
typedef  TYPE_2__ lr_write_t ;
struct TYPE_13__ {scalar_t__ lrc_txtype; } ;
typedef  TYPE_3__ lr_t ;
typedef  TYPE_4__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_IS_HOLE (TYPE_4__*) ; 
 scalar_t__ TX_WRITE ; 
 int /*<<< orphan*/  dmu_tx_get_txg (void*) ; 
 scalar_t__ zil_bp_tree_add (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  zio_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static int
zil_free_log_record(zilog_t *zilog, lr_t *lrc, void *tx, uint64_t claim_txg)
{
	lr_write_t *lr = (lr_write_t *)lrc;
	blkptr_t *bp = &lr->lr_blkptr;

	/*
	 * If we previously claimed it, we need to free it.
	 */
	if (claim_txg != 0 && lrc->lrc_txtype == TX_WRITE &&
	    bp->blk_birth >= claim_txg && zil_bp_tree_add(zilog, bp) == 0 &&
	    !BP_IS_HOLE(bp))
		zio_free(zilog->zl_spa, dmu_tx_get_txg(tx), bp);

	return (0);
}