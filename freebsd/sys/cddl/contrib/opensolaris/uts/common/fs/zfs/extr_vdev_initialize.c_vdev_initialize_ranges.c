#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* vdev_initialize_tree; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_11__ {int rs_end; int rs_start; } ;
typedef  TYPE_3__ range_seg_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_9__ {int /*<<< orphan*/  rt_root; } ;

/* Variables and functions */
 TYPE_3__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int VDEV_LABEL_START_SIZE ; 
 TYPE_3__* avl_first (int /*<<< orphan*/ *) ; 
 int vdev_initialize_write (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_initialize_chunk_size ; 

__attribute__((used)) static int
vdev_initialize_ranges(vdev_t *vd, abd_t *data)
{
	avl_tree_t *rt = &vd->vdev_initialize_tree->rt_root;

	for (range_seg_t *rs = avl_first(rt); rs != NULL;
	    rs = AVL_NEXT(rt, rs)) {
		uint64_t size = rs->rs_end - rs->rs_start;

		/* Split range into legally-sized physical chunks */
		uint64_t writes_required =
		    ((size - 1) / zfs_initialize_chunk_size) + 1;

		for (uint64_t w = 0; w < writes_required; w++) {
			int error;

			error = vdev_initialize_write(vd,
			    VDEV_LABEL_START_SIZE + rs->rs_start +
			    (w * zfs_initialize_chunk_size),
			    MIN(size - (w * zfs_initialize_chunk_size),
			    zfs_initialize_chunk_size), data);
			if (error != 0)
				return (error);
		}
	}
	return (0);
}