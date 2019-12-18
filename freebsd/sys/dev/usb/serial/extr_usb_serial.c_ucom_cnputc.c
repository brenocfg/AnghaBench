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
 int UCOM_CONS_BUFSIZE ; 
 int /*<<< orphan*/  UCOM_MTX_LOCK (struct ucom_softc*) ; 
 int /*<<< orphan*/  UCOM_MTX_UNLOCK (struct ucom_softc*) ; 
 scalar_t__ USB_IN_POLLING_MODE_FUNC () ; 
 int /*<<< orphan*/  stub1 (struct ucom_softc*) ; 
 struct ucom_softc* ucom_cons_softc ; 
 int* ucom_cons_tx_buf ; 
 size_t ucom_cons_tx_high ; 
 int ucom_cons_tx_low ; 
 int /*<<< orphan*/  ucom_outwakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ucom_cnputc(struct consdev *cd, int c)
{
	struct ucom_softc *sc = ucom_cons_softc;
	unsigned int temp;

	if (sc == NULL)
		return;

 repeat:

	UCOM_MTX_LOCK(sc);

	/* compute maximum TX length */

	temp = (UCOM_CONS_BUFSIZE - 1) - ucom_cons_tx_high + ucom_cons_tx_low;
	temp %= UCOM_CONS_BUFSIZE;

	if (temp) {
		ucom_cons_tx_buf[ucom_cons_tx_high] = c;
		ucom_cons_tx_high ++;
		ucom_cons_tx_high %= UCOM_CONS_BUFSIZE;
	}

	/* start USB transfers */
	ucom_outwakeup(sc->sc_tty);

	UCOM_MTX_UNLOCK(sc);

	/* poll if necessary */
	if (USB_IN_POLLING_MODE_FUNC() && sc->sc_callback->ucom_poll) {
		(sc->sc_callback->ucom_poll) (sc);
		/* simple flow control */
		if (temp == 0)
			goto repeat;
	}
}