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
struct stack {int dummy; } ;
struct bio {scalar_t__ bio_cmd; int bio_flags; int /*<<< orphan*/  bio_children; int /*<<< orphan*/  bio_track_bp; int /*<<< orphan*/  bio_classifier2; int /*<<< orphan*/  bio_classifier1; int /*<<< orphan*/  bio_zone; int /*<<< orphan*/  bio_attribute; int /*<<< orphan*/  bio_ma_offset; int /*<<< orphan*/  bio_ma_n; int /*<<< orphan*/  bio_ma; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_offset; int /*<<< orphan*/  bio_length; struct bio* bio_parent; } ;

/* Variables and functions */
 int BIO_ORDERED ; 
 int BIO_UNMAPPED ; 
 int BIO_VLIST ; 
 scalar_t__ BIO_ZONE ; 
 int /*<<< orphan*/  CTR2 (int,char*,struct bio*,struct bio*) ; 
 int /*<<< orphan*/  CTRSTACK (int,struct stack*,int) ; 
 int KTR_COMPILE ; 
 int KTR_GEOM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  biozone ; 
 int ktr_mask ; 
 int /*<<< orphan*/  stack_save (struct stack*) ; 
 struct bio* uma_zalloc (int /*<<< orphan*/ ,int) ; 

struct bio *
g_clone_bio(struct bio *bp)
{
	struct bio *bp2;

	bp2 = uma_zalloc(biozone, M_NOWAIT | M_ZERO);
	if (bp2 != NULL) {
		bp2->bio_parent = bp;
		bp2->bio_cmd = bp->bio_cmd;
		/*
		 *  BIO_ORDERED flag may be used by disk drivers to enforce
		 *  ordering restrictions, so this flag needs to be cloned.
		 *  BIO_UNMAPPED and BIO_VLIST should be inherited, to properly
		 *  indicate which way the buffer is passed.
		 *  Other bio flags are not suitable for cloning.
		 */
		bp2->bio_flags = bp->bio_flags &
		    (BIO_ORDERED | BIO_UNMAPPED | BIO_VLIST);
		bp2->bio_length = bp->bio_length;
		bp2->bio_offset = bp->bio_offset;
		bp2->bio_data = bp->bio_data;
		bp2->bio_ma = bp->bio_ma;
		bp2->bio_ma_n = bp->bio_ma_n;
		bp2->bio_ma_offset = bp->bio_ma_offset;
		bp2->bio_attribute = bp->bio_attribute;
		if (bp->bio_cmd == BIO_ZONE)
			bcopy(&bp->bio_zone, &bp2->bio_zone,
			    sizeof(bp->bio_zone));
		/* Inherit classification info from the parent */
		bp2->bio_classifier1 = bp->bio_classifier1;
		bp2->bio_classifier2 = bp->bio_classifier2;
#if defined(BUF_TRACKING) || defined(FULL_BUF_TRACKING)
		bp2->bio_track_bp = bp->bio_track_bp;
#endif
		bp->bio_children++;
	}
#ifdef KTR
	if ((KTR_COMPILE & KTR_GEOM) && (ktr_mask & KTR_GEOM)) {
		struct stack st;

		CTR2(KTR_GEOM, "g_clone_bio(%p): %p", bp, bp2);
		stack_save(&st);
		CTRSTACK(KTR_GEOM, &st, 3);
	}
#endif
	return(bp2);
}