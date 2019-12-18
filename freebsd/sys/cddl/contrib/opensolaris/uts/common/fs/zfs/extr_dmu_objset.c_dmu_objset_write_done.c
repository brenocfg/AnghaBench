#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int io_flags; int /*<<< orphan*/  io_bp_orig; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_5__ {int /*<<< orphan*/ * os_synctx; int /*<<< orphan*/ * os_dsl_dataset; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ZIO_FLAG_IO_REWRITE ; 
 int /*<<< orphan*/  dsl_dataset_block_born (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_block_kill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
dmu_objset_write_done(zio_t *zio, arc_buf_t *abuf, void *arg)
{
	blkptr_t *bp = zio->io_bp;
	blkptr_t *bp_orig = &zio->io_bp_orig;
	objset_t *os = arg;

	if (zio->io_flags & ZIO_FLAG_IO_REWRITE) {
		ASSERT(BP_EQUAL(bp, bp_orig));
	} else {
		dsl_dataset_t *ds = os->os_dsl_dataset;
		dmu_tx_t *tx = os->os_synctx;

		(void) dsl_dataset_block_kill(ds, bp_orig, tx, B_TRUE);
		dsl_dataset_block_born(ds, bp, tx);
	}
	kmem_free(bp, sizeof (*bp));
}