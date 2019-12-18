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
typedef  int /*<<< orphan*/  uint8_t ;
struct md_s {int /*<<< orphan*/ * pl_ptr; } ;
struct bio {int bio_offset; int bio_cmd; int bio_flags; scalar_t__ bio_resid; int /*<<< orphan*/  bio_length; int /*<<< orphan*/ * bio_data; int /*<<< orphan*/  bio_ma_offset; } ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
#define  BIO_READ 129 
 int BIO_VLIST ; 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_flush_dcache (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdcopyfrom_vlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdcopyto_vlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mdstart_preload(struct md_s *sc, struct bio *bp)
{
	uint8_t *p;

	p = sc->pl_ptr + bp->bio_offset;
	switch (bp->bio_cmd) {
	case BIO_READ:
		if ((bp->bio_flags & BIO_VLIST) != 0) {
			mdcopyto_vlist(p, (bus_dma_segment_t *)bp->bio_data,
			    bp->bio_ma_offset, bp->bio_length);
		} else {
			bcopy(p, bp->bio_data, bp->bio_length);
		}
		cpu_flush_dcache(bp->bio_data, bp->bio_length);
		break;
	case BIO_WRITE:
		if ((bp->bio_flags & BIO_VLIST) != 0) {
			mdcopyfrom_vlist((bus_dma_segment_t *)bp->bio_data,
			    bp->bio_ma_offset, p, bp->bio_length);
		} else {
			bcopy(bp->bio_data, p, bp->bio_length);
		}
		break;
	}
	bp->bio_resid = 0;
	return (0);
}