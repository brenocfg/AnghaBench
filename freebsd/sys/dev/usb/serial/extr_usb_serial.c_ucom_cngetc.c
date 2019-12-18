#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucom_softc {TYPE_1__* sc_callback; int /*<<< orphan*/  sc_tty; } ;
struct consdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ucom_poll ) (struct ucom_softc*) ;} ;

/* Variables and functions */
 size_t UCOM_CONS_BUFSIZE ; 
 int /*<<< orphan*/  UCOM_MTX_LOCK (struct ucom_softc*) ; 
 int /*<<< orphan*/  UCOM_MTX_UNLOCK (struct ucom_softc*) ; 
 scalar_t__ USB_IN_POLLING_MODE_FUNC () ; 
 int /*<<< orphan*/  stub1 (struct ucom_softc*) ; 
 int* ucom_cons_rx_buf ; 
 size_t ucom_cons_rx_high ; 
 size_t ucom_cons_rx_low ; 
 struct ucom_softc* ucom_cons_softc ; 
 int /*<<< orphan*/  ucom_outwakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ucom_cngetc(struct consdev *cd)
{
	struct ucom_softc *sc = ucom_cons_softc;
	int c;

	if (sc == NULL)
		return (-1);

	UCOM_MTX_LOCK(sc);

	if (ucom_cons_rx_low != ucom_cons_rx_high) {
		c = ucom_cons_rx_buf[ucom_cons_rx_low];
		ucom_cons_rx_low ++;
		ucom_cons_rx_low %= UCOM_CONS_BUFSIZE;
	} else {
		c = -1;
	}

	/* start USB transfers */
	ucom_outwakeup(sc->sc_tty);

	UCOM_MTX_UNLOCK(sc);

	/* poll if necessary */
	if (USB_IN_POLLING_MODE_FUNC() && sc->sc_callback->ucom_poll)
		(sc->sc_callback->ucom_poll) (sc);

	return (c);
}