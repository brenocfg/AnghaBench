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
struct ucom_softc {struct tty* sc_tty; } ;
struct TYPE_2__ {int c_cflag; } ;
struct tty {TYPE_1__ t_termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int HUPCL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SER_DTR ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_modem (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ucom_shutdown(struct ucom_softc *sc)
{
	struct tty *tp = sc->sc_tty;

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	DPRINTF("\n");

	/*
	 * Hang up if necessary:
	 */
	if (tp->t_termios.c_cflag & HUPCL) {
		ucom_modem(tp, 0, SER_DTR);
	}
}