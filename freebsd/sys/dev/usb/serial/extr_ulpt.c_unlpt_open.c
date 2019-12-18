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
struct usb_fifo {int dummy; } ;
struct ulpt_softc {int sc_fflags; struct usb_fifo** sc_fifo_open; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int FREAD ; 
 int FWRITE ; 
 size_t ULPT_BULK_DT_RD ; 
 size_t ULPT_BULK_DT_WR ; 
 int /*<<< orphan*/  ULPT_IFQ_MAXLEN ; 
 size_t USB_FIFO_RX ; 
 size_t USB_FIFO_TX ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_fifo_alloc_buffer (struct usb_fifo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ulpt_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
unlpt_open(struct usb_fifo *fifo, int fflags)
{
	struct ulpt_softc *sc = usb_fifo_softc(fifo);

	if (sc->sc_fflags & fflags) {
		return (EBUSY);
	}
	if (fflags & FREAD) {
		/* clear stall first */
		mtx_lock(&sc->sc_mtx);
		usbd_xfer_set_stall(sc->sc_xfer[ULPT_BULK_DT_RD]);
		mtx_unlock(&sc->sc_mtx);
		if (usb_fifo_alloc_buffer(fifo,
		    usbd_xfer_max_len(sc->sc_xfer[ULPT_BULK_DT_RD]),
		    ULPT_IFQ_MAXLEN)) {
			return (ENOMEM);
		}
		/* set which FIFO is opened */
		sc->sc_fifo_open[USB_FIFO_RX] = fifo;
	}
	if (fflags & FWRITE) {
		/* clear stall first */
		mtx_lock(&sc->sc_mtx);
		usbd_xfer_set_stall(sc->sc_xfer[ULPT_BULK_DT_WR]);
		mtx_unlock(&sc->sc_mtx);
		if (usb_fifo_alloc_buffer(fifo,
		    usbd_xfer_max_len(sc->sc_xfer[ULPT_BULK_DT_WR]),
		    ULPT_IFQ_MAXLEN)) {
			return (ENOMEM);
		}
		/* set which FIFO is opened */
		sc->sc_fifo_open[USB_FIFO_TX] = fifo;
	}
	sc->sc_fflags |= fflags & (FREAD | FWRITE);
	return (0);
}