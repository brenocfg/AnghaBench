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
struct disk {int dummy; } ;
struct bio {scalar_t__ bio_offset; scalar_t__ bio_length; int bio_flags; int bio_ma_n; scalar_t__ bio_ma_offset; scalar_t__ bio_ma; void* bio_data; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ ds_len; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int BIO_UNMAPPED ; 
 int BIO_VLIST ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static void
g_disk_advance(struct disk *dp, struct bio *bp, off_t off)
{

	bp->bio_offset += off;
	bp->bio_length -= off;

	if ((bp->bio_flags & BIO_VLIST) != 0) {
		bus_dma_segment_t *seg, *end;

		seg = (bus_dma_segment_t *)bp->bio_data;
		end = (bus_dma_segment_t *)bp->bio_data + bp->bio_ma_n;
		off += bp->bio_ma_offset;
		while (off >= seg->ds_len) {
			KASSERT((seg != end),
			    ("vlist request runs off the end"));
			off -= seg->ds_len;
			seg++;
		}
		bp->bio_ma_offset = off;
		bp->bio_ma_n = end - seg;
		bp->bio_data = (void *)seg;
	} else if ((bp->bio_flags & BIO_UNMAPPED) != 0) {
		bp->bio_ma += off / PAGE_SIZE;
		bp->bio_ma_offset += off;
		bp->bio_ma_offset %= PAGE_SIZE;
		bp->bio_ma_n -= off / PAGE_SIZE;
	} else {
		bp->bio_data += off;
	}
}