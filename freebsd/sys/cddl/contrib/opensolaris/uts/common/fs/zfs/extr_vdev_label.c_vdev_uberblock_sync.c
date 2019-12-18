#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_13__ {size_t vdev_children; TYPE_1__* vdev_ops; struct TYPE_13__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_14__ {int ub_txg; } ;
typedef  TYPE_3__ uberblock_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_12__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int VDEV_LABELS ; 
 int VDEV_UBERBLOCK_COUNT (TYPE_2__*) ; 
 int /*<<< orphan*/  VDEV_UBERBLOCK_OFFSET (TYPE_2__*,int) ; 
 int /*<<< orphan*/  VDEV_UBERBLOCK_SIZE (TYPE_2__*) ; 
 int ZIO_FLAG_DONT_PROPAGATE ; 
 int /*<<< orphan*/ * abd_alloc_for_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_copy_from_buf (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_zero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_write (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  vdev_uberblock_sync_done ; 
 int /*<<< orphan*/  vdev_writeable (TYPE_2__*) ; 

__attribute__((used)) static void
vdev_uberblock_sync(zio_t *zio, uint64_t *good_writes,
    uberblock_t *ub, vdev_t *vd, int flags)
{
	for (uint64_t c = 0; c < vd->vdev_children; c++) {
		vdev_uberblock_sync(zio, good_writes,
		    ub, vd->vdev_child[c], flags);
	}

	if (!vd->vdev_ops->vdev_op_leaf)
		return;

	if (!vdev_writeable(vd))
		return;

	int n = ub->ub_txg & (VDEV_UBERBLOCK_COUNT(vd) - 1);

	/* Copy the uberblock_t into the ABD */
	abd_t *ub_abd = abd_alloc_for_io(VDEV_UBERBLOCK_SIZE(vd), B_TRUE);
	abd_zero(ub_abd, VDEV_UBERBLOCK_SIZE(vd));
	abd_copy_from_buf(ub_abd, ub, sizeof (uberblock_t));

	for (int l = 0; l < VDEV_LABELS; l++)
		vdev_label_write(zio, vd, l, ub_abd,
		    VDEV_UBERBLOCK_OFFSET(vd, n), VDEV_UBERBLOCK_SIZE(vd),
		    vdev_uberblock_sync_done, good_writes,
		    flags | ZIO_FLAG_DONT_PROPAGATE);

	abd_free(ub_abd);
}