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
struct cfi_softc {int dummy; } ;
struct cfi_disk_softc {int /*<<< orphan*/  qlock; int /*<<< orphan*/  bioq; struct cfi_softc* parent; } ;
struct bio {int bio_cmd; } ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfi_disk_read (struct cfi_softc*,struct bio*) ; 
 int /*<<< orphan*/  cfi_disk_write (struct cfi_softc*,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfi_io_proc(void *arg, int pending)
{
	struct cfi_disk_softc *sc = arg;
	struct cfi_softc *cfi = sc->parent;
	struct bio *bp;

	for (;;) {
		mtx_lock(&sc->qlock);
		bp = bioq_takefirst(&sc->bioq);
		mtx_unlock(&sc->qlock);
		if (bp == NULL)
			break;

		switch (bp->bio_cmd) {
		case BIO_READ:
			cfi_disk_read(cfi, bp);
			break;
		case BIO_WRITE:
			cfi_disk_write(cfi, bp);
			break;
		}
	}
}