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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct cfi_softc {int sc_width; scalar_t__ sc_size; scalar_t__ sc_writing; } ;
struct bio {scalar_t__ bio_offset; long bio_bcount; long bio_resid; scalar_t__ bio_data; scalar_t__ bio_error; int /*<<< orphan*/  bio_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 scalar_t__ cfi_block_finish (struct cfi_softc*) ; 
 void* cfi_read_raw (struct cfi_softc*,scalar_t__) ; 

__attribute__((used)) static void
cfi_disk_read(struct cfi_softc *sc, struct bio *bp)
{
	long resid;

	KASSERT(sc->sc_width == 1 || sc->sc_width == 2 || sc->sc_width == 4,
	    ("sc_width %d", sc->sc_width));

	if (sc->sc_writing) {
		bp->bio_error = cfi_block_finish(sc);
		if (bp->bio_error) {
			bp->bio_flags |= BIO_ERROR;
			goto done;
		}
	}
	if (bp->bio_offset > sc->sc_size) {
		bp->bio_flags |= BIO_ERROR;
		bp->bio_error = EIO;
		goto done;
	}
	resid = bp->bio_bcount;
	if (sc->sc_width == 1) {
		uint8_t *dp = (uint8_t *)bp->bio_data;
		while (resid > 0 && bp->bio_offset < sc->sc_size) {
			*dp++ = cfi_read_raw(sc, bp->bio_offset);
			bp->bio_offset += 1, resid -= 1;
		}
	} else if (sc->sc_width == 2) {
		uint16_t *dp = (uint16_t *)bp->bio_data;
		while (resid > 0 && bp->bio_offset < sc->sc_size) {
			*dp++ = cfi_read_raw(sc, bp->bio_offset);
			bp->bio_offset += 2, resid -= 2;
		}
	} else {
		uint32_t *dp = (uint32_t *)bp->bio_data;
		while (resid > 0 && bp->bio_offset < sc->sc_size) {
			*dp++ = cfi_read_raw(sc, bp->bio_offset);
			bp->bio_offset += 4, resid -= 4;
		}
	}
	bp->bio_resid = resid;
done:
	biodone(bp);
}