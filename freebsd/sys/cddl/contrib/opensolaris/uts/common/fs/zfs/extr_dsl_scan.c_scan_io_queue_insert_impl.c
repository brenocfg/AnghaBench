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
struct TYPE_11__ {int /*<<< orphan*/  sio_offset; int /*<<< orphan*/  sio_asize; } ;
typedef  TYPE_2__ scan_io_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  scn_bytes_pending; } ;
typedef  TYPE_3__ dsl_scan_t ;
struct TYPE_13__ {int /*<<< orphan*/  q_exts_by_addr; int /*<<< orphan*/  q_sios_by_addr; TYPE_1__* q_vd; TYPE_3__* q_scn; } ;
typedef  TYPE_4__ dsl_scan_io_queue_t ;
typedef  int /*<<< orphan*/  avl_index_t ;
struct TYPE_10__ {int /*<<< orphan*/  vdev_scan_io_queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  range_tree_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scan_io_queue_insert_impl(dsl_scan_io_queue_t *queue, scan_io_t *sio)
{
	avl_index_t idx;
	int64_t asize = sio->sio_asize;
	dsl_scan_t *scn = queue->q_scn;

	ASSERT(MUTEX_HELD(&queue->q_vd->vdev_scan_io_queue_lock));

	if (avl_find(&queue->q_sios_by_addr, sio, &idx) != NULL) {
		/* block is already scheduled for reading */
		atomic_add_64(&scn->scn_bytes_pending, -asize);
		kmem_free(sio, sizeof (*sio));
		return;
	}
	avl_insert(&queue->q_sios_by_addr, sio, idx);
	range_tree_add(queue->q_exts_by_addr, sio->sio_offset, asize);
}