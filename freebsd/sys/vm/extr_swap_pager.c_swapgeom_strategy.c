#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vm_offset_t ;
struct swdevt {int sw_first; struct g_consumer* sw_id; } ;
struct g_consumer {int dummy; } ;
struct buf {scalar_t__ b_iocmd; int b_blkno; int /*<<< orphan*/  b_data; int /*<<< orphan*/  b_npages; scalar_t__ b_offset; int /*<<< orphan*/ * b_pages; int /*<<< orphan*/  b_bcount; struct bio* b_caller1; int /*<<< orphan*/  b_ioflags; int /*<<< orphan*/  b_error; } ;
struct bio {scalar_t__ bio_cmd; int bio_offset; int bio_ma_offset; int /*<<< orphan*/ * bio_ma; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_flags; int /*<<< orphan*/  bio_ma_n; int /*<<< orphan*/  bio_done; int /*<<< orphan*/  bio_length; struct buf* bio_caller2; struct swdevt* bio_caller1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  BIO_UNMAPPED ; 
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  buf_mapped (struct buf*) ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 struct bio* g_new_bio () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sw_dev_mtx ; 
 int /*<<< orphan*/  swapgeom_acquire (struct g_consumer*) ; 
 int /*<<< orphan*/  swapgeom_done ; 
 int /*<<< orphan*/  swapgeom_release (struct g_consumer*,struct swdevt*) ; 
 int /*<<< orphan*/  unmapped_buf ; 

__attribute__((used)) static void
swapgeom_strategy(struct buf *bp, struct swdevt *sp)
{
	struct bio *bio;
	struct g_consumer *cp;

	mtx_lock(&sw_dev_mtx);
	cp = sp->sw_id;
	if (cp == NULL) {
		mtx_unlock(&sw_dev_mtx);
		bp->b_error = ENXIO;
		bp->b_ioflags |= BIO_ERROR;
		bufdone(bp);
		return;
	}
	swapgeom_acquire(cp);
	mtx_unlock(&sw_dev_mtx);
	if (bp->b_iocmd == BIO_WRITE)
		bio = g_new_bio();
	else
		bio = g_alloc_bio();
	if (bio == NULL) {
		mtx_lock(&sw_dev_mtx);
		swapgeom_release(cp, sp);
		mtx_unlock(&sw_dev_mtx);
		bp->b_error = ENOMEM;
		bp->b_ioflags |= BIO_ERROR;
		printf("swap_pager: cannot allocate bio\n");
		bufdone(bp);
		return;
	}

	bp->b_caller1 = bio;
	bio->bio_caller1 = sp;
	bio->bio_caller2 = bp;
	bio->bio_cmd = bp->b_iocmd;
	bio->bio_offset = (bp->b_blkno - sp->sw_first) * PAGE_SIZE;
	bio->bio_length = bp->b_bcount;
	bio->bio_done = swapgeom_done;
	if (!buf_mapped(bp)) {
		bio->bio_ma = bp->b_pages;
		bio->bio_data = unmapped_buf;
		bio->bio_ma_offset = (vm_offset_t)bp->b_offset & PAGE_MASK;
		bio->bio_ma_n = bp->b_npages;
		bio->bio_flags |= BIO_UNMAPPED;
	} else {
		bio->bio_data = bp->b_data;
		bio->bio_ma = NULL;
	}
	g_io_request(bio, cp);
	return;
}