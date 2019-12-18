#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  zl_spa; } ;
typedef  TYPE_1__ zilog_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {scalar_t__ blk_birth; } ;
typedef  TYPE_2__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_IS_HOLE (TYPE_2__*) ; 
 scalar_t__ zil_bp_tree_add (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zio_free (int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 

__attribute__((used)) static int
zil_clear_log_block(zilog_t *zilog, blkptr_t *bp, void *tx, uint64_t first_txg)
{
	ASSERT(!BP_IS_HOLE(bp));

	/*
	 * As we call this function from the context of a rewind to a
	 * checkpoint, each ZIL block whose txg is later than the txg
	 * that we rewind to is invalid. Thus, we return -1 so
	 * zil_parse() doesn't attempt to read it.
	 */
	if (bp->blk_birth >= first_txg)
		return (-1);

	if (zil_bp_tree_add(zilog, bp) != 0)
		return (0);

	zio_free(zilog->zl_spa, first_txg, bp);
	return (0);
}