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
struct urio_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  URIO_FLAG_READ_STALL ; 
 int /*<<< orphan*/  URIO_FLAG_WRITE_STALL ; 
 int /*<<< orphan*/  URIO_IFQ_MAXLEN ; 
 size_t URIO_T_RD ; 
 size_t URIO_T_WR ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_fifo_alloc_buffer (struct usb_fifo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct urio_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
urio_open(struct usb_fifo *fifo, int fflags)
{
	struct urio_softc *sc = usb_fifo_softc(fifo);

	if (fflags & FREAD) {
		/* clear stall first */
		mtx_lock(&sc->sc_mtx);
		sc->sc_flags |= URIO_FLAG_READ_STALL;
		mtx_unlock(&sc->sc_mtx);

		if (usb_fifo_alloc_buffer(fifo,
		    usbd_xfer_max_len(sc->sc_xfer[URIO_T_RD]),
		    URIO_IFQ_MAXLEN)) {
			return (ENOMEM);
		}
	}
	if (fflags & FWRITE) {
		/* clear stall first */
		sc->sc_flags |= URIO_FLAG_WRITE_STALL;

		if (usb_fifo_alloc_buffer(fifo,
		    usbd_xfer_max_len(sc->sc_xfer[URIO_T_WR]),
		    URIO_IFQ_MAXLEN)) {
			return (ENOMEM);
		}
	}
	return (0);			/* success */
}