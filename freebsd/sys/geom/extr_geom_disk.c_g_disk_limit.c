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
struct disk {int dummy; } ;
struct bio {scalar_t__ bio_length; int bio_flags; int bio_ma_n; scalar_t__ bio_ma_offset; scalar_t__ bio_data; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int BIO_UNMAPPED ; 
 int BIO_VLIST ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ g_disk_maxsize (struct disk*,struct bio*) ; 
 scalar_t__ g_disk_vlist_limit (struct disk*,struct bio*,int /*<<< orphan*/ **) ; 
 int howmany (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
g_disk_limit(struct disk *dp, struct bio *bp)
{
	bool limited = false;
	off_t maxsz;

	maxsz = g_disk_maxsize(dp, bp);

	/*
	 * XXX: If we have a stripesize we should really use it here.
	 *      Care should be taken in the delete case if this is done
	 *      as deletes can be very sensitive to size given how they
	 *      are processed.
	 */
	if (bp->bio_length > maxsz) {
		bp->bio_length = maxsz;
		limited = true;
	}

	if ((bp->bio_flags & BIO_VLIST) != 0) {
		bus_dma_segment_t *firstseg, *endseg;
		off_t residual;

		firstseg = (bus_dma_segment_t*)bp->bio_data;
		residual = g_disk_vlist_limit(dp, bp, &endseg);
		if (residual != 0) {
			bp->bio_ma_n = endseg - firstseg;
			bp->bio_length -= residual;
			limited = true;
		}
	} else if ((bp->bio_flags & BIO_UNMAPPED) != 0) {
		bp->bio_ma_n =
		    howmany(bp->bio_ma_offset + bp->bio_length, PAGE_SIZE);
	}

	return (limited);
}