#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_7__ {size_t spa_syncing_txg; int /*<<< orphan*/ * spa_free_bplist; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 scalar_t__ BP_GET_DEDUP (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_GET_PSIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_IS_EMBEDDED (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_IS_GANG (int /*<<< orphan*/  const*) ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bplist_append (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  metaslab_check_free (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ spa_sync_pass (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_blkptr_verify (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ zfs_sync_pass_deferred_free ; 
 scalar_t__ zfs_trim_enabled ; 
 int /*<<< orphan*/  zio_free_sync (int /*<<< orphan*/ *,TYPE_1__*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ ) ; 

void
zio_free(spa_t *spa, uint64_t txg, const blkptr_t *bp)
{

	zfs_blkptr_verify(spa, bp);

	/*
	 * The check for EMBEDDED is a performance optimization.  We
	 * process the free here (by ignoring it) rather than
	 * putting it on the list and then processing it in zio_free_sync().
	 */
	if (BP_IS_EMBEDDED(bp))
		return;
	metaslab_check_free(spa, bp);

	/*
	 * Frees that are for the currently-syncing txg, are not going to be
	 * deferred, and which will not need to do a read (i.e. not GANG or
	 * DEDUP), can be processed immediately.  Otherwise, put them on the
	 * in-memory list for later processing.
	 */
	if (zfs_trim_enabled || BP_IS_GANG(bp) || BP_GET_DEDUP(bp) ||
	    txg != spa->spa_syncing_txg ||
	    spa_sync_pass(spa) >= zfs_sync_pass_deferred_free) {
		bplist_append(&spa->spa_free_bplist[txg & TXG_MASK], bp);
	} else {
		VERIFY0(zio_wait(zio_free_sync(NULL, spa, txg, bp,
		    BP_GET_PSIZE(bp), 0)));
	}
}