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
struct uio {int /*<<< orphan*/  uio_resid; } ;
struct cmx_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * buf; int /*<<< orphan*/  timeout; scalar_t__ dying; } ;
struct cdev {struct cmx_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSR_BULK_OUT_FULL ; 
 int /*<<< orphan*/  CCID_DRIVER_MINIMUM_TIMEOUT ; 
 int /*<<< orphan*/  CMX_MIN_WRLEN ; 
 int /*<<< orphan*/  DEBUG_printf (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int ENXIO ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MODEBITS ; 
 int /*<<< orphan*/  SCR_HOST_TO_READER_DONE ; 
 int /*<<< orphan*/  SCR_HOST_TO_READER_START ; 
 int cmx_sync_write_SCR (struct cmx_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmx_timeout_by_cmd (int /*<<< orphan*/ ) ; 
 int cmx_wait_BSR (struct cmx_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmx_write_DTR (struct cmx_softc*,int /*<<< orphan*/ ) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
cmx_write(struct cdev *cdev, struct uio *uio, int flag)
{
	struct cmx_softc *sc = cdev->si_drv1;
	int rv, amnt;

	if (sc == NULL || sc->dying)
		return ENXIO;

	DEBUG_printf(sc->dev, "called (len=%d flag=%b)\n",
			uio->uio_resid, flag, MODEBITS);

	if (uio->uio_resid == 0) {
		return 0;
	}

	if (uio->uio_resid < CMX_MIN_WRLEN) {
		return EINVAL;
	}

	if ((rv = cmx_sync_write_SCR(sc, SCR_HOST_TO_READER_START)) != 0) {
		return rv;
	}

	sc->timeout = 0;
	while (uio->uio_resid > 0) {
		amnt = MIN(uio->uio_resid, sizeof(sc->buf));

		if ((rv = uiomove(sc->buf, amnt, uio)) != 0) {
			DEBUG_printf(sc->dev, "uiomove failed (%d)\n", rv);
			/* wildly guessed attempt to notify device */
			sc->timeout = CCID_DRIVER_MINIMUM_TIMEOUT;
			cmx_sync_write_SCR(sc, SCR_HOST_TO_READER_DONE);
			return rv;
		}

		if (sc->timeout == 0) {
			sc->timeout = cmx_timeout_by_cmd(sc->buf[0]);
			DEBUG_printf(sc->dev, "cmd=%02x timeout=%lu\n",
					sc->buf[0], sc->timeout);
		}

		for (int i = 0; i < amnt; i++) {
			if ((rv = cmx_wait_BSR(sc, BSR_BULK_OUT_FULL, 0))!=0) {
				return rv;
			}
			cmx_write_DTR(sc, sc->buf[i]);
			DEBUG_printf(sc->dev, "buf[%02x]=%02x\n",
					i, sc->buf[i]);
		}
	}

	if ((rv = cmx_sync_write_SCR(sc, SCR_HOST_TO_READER_DONE)) != 0) {
		return rv;
	}

	DEBUG_printf(sc->dev, "success\n");
	return 0;
}