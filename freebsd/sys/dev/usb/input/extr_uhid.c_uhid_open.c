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
struct uhid_softc {scalar_t__ sc_osize; scalar_t__ sc_isize; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  UHID_FLAG_IMMED ; 
 int /*<<< orphan*/  UHID_FRAME_NUM ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_fifo_alloc_buffer (struct usb_fifo*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct uhid_softc* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static int
uhid_open(struct usb_fifo *fifo, int fflags)
{
	struct uhid_softc *sc = usb_fifo_softc(fifo);

	/*
	 * The buffers are one byte larger than maximum so that one
	 * can detect too large read/writes and short transfers:
	 */
	if (fflags & FREAD) {
		/* reset flags */
		mtx_lock(&sc->sc_mtx);
		sc->sc_flags &= ~UHID_FLAG_IMMED;
		mtx_unlock(&sc->sc_mtx);

		if (usb_fifo_alloc_buffer(fifo,
		    sc->sc_isize + 1, UHID_FRAME_NUM)) {
			return (ENOMEM);
		}
	}
	if (fflags & FWRITE) {
		if (usb_fifo_alloc_buffer(fifo,
		    sc->sc_osize + 1, UHID_FRAME_NUM)) {
			return (ENOMEM);
		}
	}
	return (0);
}