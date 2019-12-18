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
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_11__ {int sio_flags; int /*<<< orphan*/  sio_asize; int /*<<< orphan*/  sio_zb; } ;
typedef  TYPE_2__ scan_io_t ;
struct TYPE_12__ {int /*<<< orphan*/  scn_bytes_pending; } ;
typedef  TYPE_3__ dsl_scan_t ;
struct TYPE_13__ {TYPE_1__* q_vd; TYPE_3__* q_scn; } ;
typedef  TYPE_4__ dsl_scan_io_queue_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_10__ {int /*<<< orphan*/  vdev_scan_io_queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_IS_GANG (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp2sio (int /*<<< orphan*/  const*,TYPE_2__*,int) ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_io_queue_insert_impl (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static void
scan_io_queue_insert(dsl_scan_io_queue_t *queue, const blkptr_t *bp, int dva_i,
    int zio_flags, const zbookmark_phys_t *zb)
{
	dsl_scan_t *scn = queue->q_scn;
	scan_io_t *sio = kmem_zalloc(sizeof (*sio), KM_SLEEP);

	ASSERT0(BP_IS_GANG(bp));
	ASSERT(MUTEX_HELD(&queue->q_vd->vdev_scan_io_queue_lock));

	bp2sio(bp, sio, dva_i);
	sio->sio_flags = zio_flags;
	sio->sio_zb = *zb;

	/*
	 * Increment the bytes pending counter now so that we can't
	 * get an integer underflow in case the worker processes the
	 * zio before we get to incrementing this counter.
	 */
	atomic_add_64(&scn->scn_bytes_pending, sio->sio_asize);

	scan_io_queue_insert_impl(queue, sio);
}