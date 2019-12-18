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
struct opalflash_softc {int /*<<< orphan*/  sc_bio_queue; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;
struct bio {int bio_cmd; int /*<<< orphan*/  bio_error; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_offset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BIO_DELETE 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  OPALFLASH_LOCK (struct opalflash_softc*) ; 
 int /*<<< orphan*/  OPALFLASH_UNLOCK (struct opalflash_softc*) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  msleep (struct opalflash_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opalflash_erase (struct opalflash_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opalflash_read (struct opalflash_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opalflash_write (struct opalflash_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
opalflash_task(void *arg)
{
	struct opalflash_softc *sc;
	struct bio *bp;
	device_t dev;

	sc = arg;

	for (;;) {
		dev = sc->sc_dev;
		OPALFLASH_LOCK(sc);
		do {
			bp = bioq_first(&sc->sc_bio_queue);
			if (bp == NULL)
				msleep(sc, &sc->sc_mtx, PRIBIO, "opalflash", 0);
		} while (bp == NULL);
		bioq_remove(&sc->sc_bio_queue, bp);
		OPALFLASH_UNLOCK(sc);

		switch (bp->bio_cmd) {
		case BIO_DELETE:
			bp->bio_error = opalflash_erase(sc, bp->bio_offset,
			    bp->bio_bcount);
			break;
		case BIO_READ:
			bp->bio_error = opalflash_read(sc, bp->bio_offset,
			    bp->bio_data, bp->bio_bcount);
			break;
		case BIO_WRITE:
			bp->bio_error = opalflash_write(sc, bp->bio_offset,
			    bp->bio_data, bp->bio_bcount);
			break;
		default:
			bp->bio_error = EINVAL;
		}
		biodone(bp);
	}
}