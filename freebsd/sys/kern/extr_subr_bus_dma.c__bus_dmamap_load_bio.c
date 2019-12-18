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
struct bio {int bio_flags; int /*<<< orphan*/  bio_bcount; scalar_t__ bio_data; int /*<<< orphan*/  bio_ma_offset; int /*<<< orphan*/  bio_ma; int /*<<< orphan*/  bio_ma_n; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int BIO_UNMAPPED ; 
 int BIO_VLIST ; 
 int _bus_dmamap_load_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int _bus_dmamap_load_ma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int _bus_dmamap_load_vlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 

__attribute__((used)) static int
_bus_dmamap_load_bio(bus_dma_tag_t dmat, bus_dmamap_t map, struct bio *bio,
    int *nsegs, int flags)
{

	if ((bio->bio_flags & BIO_VLIST) != 0) {
		bus_dma_segment_t *segs = (bus_dma_segment_t *)bio->bio_data;
		return (_bus_dmamap_load_vlist(dmat, map, segs, bio->bio_ma_n,
		    kernel_pmap, nsegs, flags, bio->bio_ma_offset,
		    bio->bio_bcount));
	}

	if ((bio->bio_flags & BIO_UNMAPPED) != 0)
		return (_bus_dmamap_load_ma(dmat, map, bio->bio_ma,
		    bio->bio_bcount, bio->bio_ma_offset, flags, NULL, nsegs));

	return (_bus_dmamap_load_buffer(dmat, map, bio->bio_data,
	    bio->bio_bcount, kernel_pmap, flags, NULL, nsegs));
}