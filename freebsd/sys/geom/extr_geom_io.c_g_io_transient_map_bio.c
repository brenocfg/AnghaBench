#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ u_int ;
struct bio {long bio_ma_n; int /*<<< orphan*/  bio_flags; scalar_t__ bio_ma_offset; scalar_t__ bio_data; int /*<<< orphan*/  bio_ma; TYPE_1__* bio_to; scalar_t__ bio_length; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TRANSIENT_MAPPING ; 
 int /*<<< orphan*/  BIO_UNMAPPED ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct bio*,int /*<<< orphan*/ ,scalar_t__) ; 
 int EDEADLK ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_GEOM ; 
 int M_BESTFIT ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  OFF_TO_IDX (long) ; 
 long PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int hz ; 
 int /*<<< orphan*/  inflight_transient_maps ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  pmap_qenter (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long round_page (scalar_t__) ; 
 int /*<<< orphan*/  transient_arena ; 
 int /*<<< orphan*/  transient_map_hard_failures ; 
 scalar_t__ transient_map_retries ; 
 int /*<<< orphan*/  transient_map_soft_failures ; 
 int /*<<< orphan*/  transient_maps ; 
 int unmapped_buf_allowed ; 
 scalar_t__ vmem_alloc (int /*<<< orphan*/ ,long,int,scalar_t__*) ; 

__attribute__((used)) static int
g_io_transient_map_bio(struct bio *bp)
{
	vm_offset_t addr;
	long size;
	u_int retried;

	KASSERT(unmapped_buf_allowed, ("unmapped disabled"));

	size = round_page(bp->bio_ma_offset + bp->bio_length);
	KASSERT(size / PAGE_SIZE == bp->bio_ma_n, ("Bio too short %p", bp));
	addr = 0;
	retried = 0;
	atomic_add_long(&transient_maps, 1);
retry:
	if (vmem_alloc(transient_arena, size, M_BESTFIT | M_NOWAIT, &addr)) {
		if (transient_map_retries != 0 &&
		    retried >= transient_map_retries) {
			CTR2(KTR_GEOM, "g_down cannot map bp %p provider %s",
			    bp, bp->bio_to->name);
			atomic_add_int(&transient_map_hard_failures, 1);
			return (EDEADLK/* XXXKIB */);
		} else {
			/*
			 * Naive attempt to quisce the I/O to get more
			 * in-flight requests completed and defragment
			 * the transient_arena.
			 */
			CTR3(KTR_GEOM, "g_down retrymap bp %p provider %s r %d",
			    bp, bp->bio_to->name, retried);
			pause("g_d_tra", hz / 10);
			retried++;
			atomic_add_int(&transient_map_soft_failures, 1);
			goto retry;
		}
	}
	atomic_add_int(&inflight_transient_maps, 1);
	pmap_qenter((vm_offset_t)addr, bp->bio_ma, OFF_TO_IDX(size));
	bp->bio_data = (caddr_t)addr + bp->bio_ma_offset;
	bp->bio_flags |= BIO_TRANSIENT_MAPPING;
	bp->bio_flags &= ~BIO_UNMAPPED;
	return (EJUSTRETURN);
}