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
struct wsp_softc {int sc_state; } ;
struct usb_fifo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int FREAD ; 
 int WSP_ENABLED ; 
 int /*<<< orphan*/  WSP_FIFO_BUF_SIZE ; 
 int /*<<< orphan*/  WSP_FIFO_QUEUE_MAXLEN ; 
 int /*<<< orphan*/  WSP_LLEVEL_INFO ; 
 scalar_t__ usb_fifo_alloc_buffer (struct usb_fifo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fifo_free_buffer (struct usb_fifo*) ; 
 struct wsp_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int wsp_enable (struct wsp_softc*) ; 

__attribute__((used)) static int
wsp_open(struct usb_fifo *fifo, int fflags)
{
	DPRINTFN(WSP_LLEVEL_INFO, "\n");

	if (fflags & FREAD) {
		struct wsp_softc *sc = usb_fifo_softc(fifo);
		int rc;

		if (sc->sc_state & WSP_ENABLED)
			return (EBUSY);

		if (usb_fifo_alloc_buffer(fifo,
		    WSP_FIFO_BUF_SIZE, WSP_FIFO_QUEUE_MAXLEN)) {
			return (ENOMEM);
		}
		rc = wsp_enable(sc);
		if (rc != 0) {
			usb_fifo_free_buffer(fifo);
			return (rc);
		}
	}
	return (0);
}