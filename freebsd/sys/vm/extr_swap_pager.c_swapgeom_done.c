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
struct swdevt {int dummy; } ;
struct g_consumer {int dummy; } ;
struct buf {int /*<<< orphan*/ * b_caller1; scalar_t__ b_error; scalar_t__ b_bcount; scalar_t__ b_resid; int /*<<< orphan*/  b_ioflags; } ;
struct bio {struct swdevt* bio_caller1; scalar_t__ bio_error; scalar_t__ bio_completed; int /*<<< orphan*/  bio_flags; struct g_consumer* bio_from; struct buf* bio_caller2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sw_dev_mtx ; 
 int /*<<< orphan*/  swapgeom_release (struct g_consumer*,struct swdevt*) ; 

__attribute__((used)) static void
swapgeom_done(struct bio *bp2)
{
	struct swdevt *sp;
	struct buf *bp;
	struct g_consumer *cp;

	bp = bp2->bio_caller2;
	cp = bp2->bio_from;
	bp->b_ioflags = bp2->bio_flags;
	if (bp2->bio_error)
		bp->b_ioflags |= BIO_ERROR;
	bp->b_resid = bp->b_bcount - bp2->bio_completed;
	bp->b_error = bp2->bio_error;
	bp->b_caller1 = NULL;
	bufdone(bp);
	sp = bp2->bio_caller1;
	mtx_lock(&sw_dev_mtx);
	swapgeom_release(cp, sp);
	mtx_unlock(&sw_dev_mtx);
	g_destroy_bio(bp2);
}