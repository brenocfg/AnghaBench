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
struct ucom_softc {int sc_flag; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct ucom_softc*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UCOM_FLAG_HL_READY ; 
 int /*<<< orphan*/  UCOM_MTX_ASSERT (struct ucom_softc*,int /*<<< orphan*/ ) ; 
 struct ucom_softc* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  ucom_start_transfers (struct ucom_softc*) ; 

__attribute__((used)) static void
ucom_outwakeup(struct tty *tp)
{
	struct ucom_softc *sc = tty_softc(tp);

	UCOM_MTX_ASSERT(sc, MA_OWNED);

	DPRINTF("sc = %p\n", sc);

	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		/* The higher layer is not ready */
		return;
	}
	ucom_start_transfers(sc);
}