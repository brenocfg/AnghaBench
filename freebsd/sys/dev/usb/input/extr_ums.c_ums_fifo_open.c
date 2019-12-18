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
struct ums_softc {int sc_fflags; scalar_t__ sc_evflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  UMS_BUF_SIZE ; 
 int /*<<< orphan*/  UMS_IFQ_MAXLEN ; 
 int /*<<< orphan*/  ums_reset (struct ums_softc*) ; 
 scalar_t__ usb_fifo_alloc_buffer (struct usb_fifo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ums_softc* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static int
ums_fifo_open(struct usb_fifo *fifo, int fflags)
{
	struct ums_softc *sc = usb_fifo_softc(fifo);

	DPRINTFN(2, "\n");

	/* check for duplicate open, should not happen */
	if (sc->sc_fflags & fflags)
		return (EBUSY);

	/* check for first open */
#ifdef EVDEV_SUPPORT
	if (sc->sc_fflags == 0 && sc->sc_evflags == 0)
		ums_reset(sc);
#else
	if (sc->sc_fflags == 0)
		ums_reset(sc);
#endif

	if (fflags & FREAD) {
		/* allocate RX buffer */
		if (usb_fifo_alloc_buffer(fifo,
		    UMS_BUF_SIZE, UMS_IFQ_MAXLEN)) {
			return (ENOMEM);
		}
	}

	sc->sc_fflags |= fflags & (FREAD | FWRITE);
	return (0);
}