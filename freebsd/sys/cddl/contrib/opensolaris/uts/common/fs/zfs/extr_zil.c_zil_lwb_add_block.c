#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zv_vdev; } ;
typedef  TYPE_1__ zil_vdev_node_t ;
struct TYPE_11__ {int /*<<< orphan*/  lwb_vdev_lock; int /*<<< orphan*/  lwb_vdev_tree; } ;
typedef  TYPE_2__ lwb_t ;
struct TYPE_12__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_3__ blkptr_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int BP_GET_NDVAS (TYPE_3__ const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zil_nocacheflush ; 

void
zil_lwb_add_block(lwb_t *lwb, const blkptr_t *bp)
{
	avl_tree_t *t = &lwb->lwb_vdev_tree;
	avl_index_t where;
	zil_vdev_node_t *zv, zvsearch;
	int ndvas = BP_GET_NDVAS(bp);
	int i;

	if (zil_nocacheflush)
		return;

	mutex_enter(&lwb->lwb_vdev_lock);
	for (i = 0; i < ndvas; i++) {
		zvsearch.zv_vdev = DVA_GET_VDEV(&bp->blk_dva[i]);
		if (avl_find(t, &zvsearch, &where) == NULL) {
			zv = kmem_alloc(sizeof (*zv), KM_SLEEP);
			zv->zv_vdev = zvsearch.zv_vdev;
			avl_insert(t, zv, where);
		}
	}
	mutex_exit(&lwb->lwb_vdev_lock);
}