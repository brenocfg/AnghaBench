#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_6__ {int /*<<< orphan*/ * mg_alloc_queue_depth; } ;
typedef  TYPE_1__ metaslab_group_t ;
typedef  int /*<<< orphan*/  dva_t ;
struct TYPE_7__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_2__ blkptr_t ;
struct TYPE_8__ {TYPE_1__* vdev_mg; } ;

/* Variables and functions */
 int BP_GET_NDVAS (TYPE_2__ const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 TYPE_3__* vdev_lookup_top (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_not_held (int /*<<< orphan*/ *,void*) ; 

void
metaslab_group_alloc_verify(spa_t *spa, const blkptr_t *bp, void *tag,
    int allocator)
{
#ifdef ZFS_DEBUG
	const dva_t *dva = bp->blk_dva;
	int ndvas = BP_GET_NDVAS(bp);

	for (int d = 0; d < ndvas; d++) {
		uint64_t vdev = DVA_GET_VDEV(&dva[d]);
		metaslab_group_t *mg = vdev_lookup_top(spa, vdev)->vdev_mg;
		VERIFY(zfs_refcount_not_held(
		    &mg->mg_alloc_queue_depth[allocator], tag));
	}
#endif
}