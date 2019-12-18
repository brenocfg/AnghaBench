#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zl_lock; int /*<<< orphan*/  zl_lwb_list; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  zil_chain_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int lwb_nused; int /*<<< orphan*/  lwb_waiters; int /*<<< orphan*/  lwb_vdev_tree; int /*<<< orphan*/  lwb_vdev_lock; void* lwb_sz; scalar_t__ lwb_issued_timestamp; int /*<<< orphan*/ * lwb_tx; int /*<<< orphan*/ * lwb_root_zio; int /*<<< orphan*/ * lwb_write_zio; int /*<<< orphan*/  lwb_max_txg; int /*<<< orphan*/  lwb_buf; int /*<<< orphan*/  lwb_state; int /*<<< orphan*/  lwb_slog; int /*<<< orphan*/  lwb_blk; TYPE_1__* lwb_zilog; } ;
typedef  TYPE_2__ lwb_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BP_GET_CHECKSUM (int /*<<< orphan*/ *) ; 
 void* BP_GET_LSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LWB_STATE_CLOSED ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 scalar_t__ ZIO_CHECKSUM_ZILOG2 ; 
 int avl_is_empty (int /*<<< orphan*/ *) ; 
 TYPE_2__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_lwb_cache ; 
 int /*<<< orphan*/  zio_buf_alloc (void*) ; 

__attribute__((used)) static lwb_t *
zil_alloc_lwb(zilog_t *zilog, blkptr_t *bp, boolean_t slog, uint64_t txg)
{
	lwb_t *lwb;

	lwb = kmem_cache_alloc(zil_lwb_cache, KM_SLEEP);
	lwb->lwb_zilog = zilog;
	lwb->lwb_blk = *bp;
	lwb->lwb_slog = slog;
	lwb->lwb_state = LWB_STATE_CLOSED;
	lwb->lwb_buf = zio_buf_alloc(BP_GET_LSIZE(bp));
	lwb->lwb_max_txg = txg;
	lwb->lwb_write_zio = NULL;
	lwb->lwb_root_zio = NULL;
	lwb->lwb_tx = NULL;
	lwb->lwb_issued_timestamp = 0;
	if (BP_GET_CHECKSUM(bp) == ZIO_CHECKSUM_ZILOG2) {
		lwb->lwb_nused = sizeof (zil_chain_t);
		lwb->lwb_sz = BP_GET_LSIZE(bp);
	} else {
		lwb->lwb_nused = 0;
		lwb->lwb_sz = BP_GET_LSIZE(bp) - sizeof (zil_chain_t);
	}

	mutex_enter(&zilog->zl_lock);
	list_insert_tail(&zilog->zl_lwb_list, lwb);
	mutex_exit(&zilog->zl_lock);

	ASSERT(!MUTEX_HELD(&lwb->lwb_vdev_lock));
	ASSERT(avl_is_empty(&lwb->lwb_vdev_tree));
	VERIFY(list_is_empty(&lwb->lwb_waiters));

	return (lwb);
}