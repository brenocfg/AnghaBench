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
struct mx25l_softc {scalar_t__ sc_taskstate; int /*<<< orphan*/  sc_bio_queue; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;
struct bio {int bio_cmd; int /*<<< orphan*/  bio_error; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_offset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  M25PXX_LOCK (struct mx25l_softc*) ; 
 int /*<<< orphan*/  M25PXX_UNLOCK (struct mx25l_softc*) ; 
 int /*<<< orphan*/  PRIBIO ; 
 scalar_t__ TSTATE_STOPPED ; 
 scalar_t__ TSTATE_STOPPING ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct mx25l_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx25l_read (struct mx25l_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx25l_write (struct mx25l_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct mx25l_softc*) ; 

__attribute__((used)) static void
mx25l_task(void *arg)
{
	struct mx25l_softc *sc = (struct mx25l_softc*)arg;
	struct bio *bp;
	device_t dev;

	for (;;) {
		dev = sc->sc_dev;
		M25PXX_LOCK(sc);
		do {
			if (sc->sc_taskstate == TSTATE_STOPPING) {
				sc->sc_taskstate = TSTATE_STOPPED;
				M25PXX_UNLOCK(sc);
				wakeup(sc);
				kproc_exit(0);
			}
			bp = bioq_first(&sc->sc_bio_queue);
			if (bp == NULL)
				msleep(sc, &sc->sc_mtx, PRIBIO, "mx25jq", 0);
		} while (bp == NULL);
		bioq_remove(&sc->sc_bio_queue, bp);
		M25PXX_UNLOCK(sc);

		switch (bp->bio_cmd) {
		case BIO_READ:
			bp->bio_error = mx25l_read(sc, bp->bio_offset, 
			    bp->bio_data, bp->bio_bcount);
			break;
		case BIO_WRITE:
			bp->bio_error = mx25l_write(sc, bp->bio_offset, 
			    bp->bio_data, bp->bio_bcount);
			break;
		default:
			bp->bio_error = EINVAL;
		}


		biodone(bp);
	}
}