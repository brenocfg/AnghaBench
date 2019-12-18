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
struct ucom_super_softc {int dummy; } ;
struct ucom_softc {int sc_flag; TYPE_1__* sc_callback; struct tty* sc_tty; int /*<<< orphan*/ * sc_consdev; } ;
struct tty {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ucom_stop_write ) (struct ucom_softc*) ;int /*<<< orphan*/  (* ucom_stop_read ) (struct ucom_softc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct ucom_softc*,struct tty*) ; 
 int /*<<< orphan*/  M_USBDEV ; 
 int UCOM_FLAG_CONSOLE ; 
 int UCOM_FLAG_GONE ; 
 int UCOM_FLAG_HL_READY ; 
 int UCOM_FLAG_LL_READY ; 
 int /*<<< orphan*/  UCOM_MTX_LOCK (struct ucom_softc*) ; 
 int /*<<< orphan*/  UCOM_MTX_UNLOCK (struct ucom_softc*) ; 
 int /*<<< orphan*/  cnremove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ucom_softc*) ; 
 int /*<<< orphan*/  stub2 (struct ucom_softc*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_gone (struct tty*) ; 
 int /*<<< orphan*/  ucom_close (struct tty*) ; 
 int /*<<< orphan*/  ucom_close_refs ; 
 struct ucom_softc* ucom_cons_softc ; 
 int /*<<< orphan*/  ucom_mtx ; 

__attribute__((used)) static void
ucom_detach_tty(struct ucom_super_softc *ssc, struct ucom_softc *sc)
{
	struct tty *tp = sc->sc_tty;

	DPRINTF("sc = %p, tp = %p\n", sc, sc->sc_tty);

	if (sc->sc_consdev != NULL) {
		cnremove(sc->sc_consdev);
		free(sc->sc_consdev, M_USBDEV);
		sc->sc_consdev = NULL;
	}

	if (sc->sc_flag & UCOM_FLAG_CONSOLE) {
		UCOM_MTX_LOCK(ucom_cons_softc);
		ucom_close(ucom_cons_softc->sc_tty);
		sc->sc_flag &= ~UCOM_FLAG_CONSOLE;
		UCOM_MTX_UNLOCK(ucom_cons_softc);
		ucom_cons_softc = NULL;
	}

	/* the config thread has been stopped when we get here */

	UCOM_MTX_LOCK(sc);
	sc->sc_flag |= UCOM_FLAG_GONE;
	sc->sc_flag &= ~(UCOM_FLAG_HL_READY | UCOM_FLAG_LL_READY);
	UCOM_MTX_UNLOCK(sc);

	if (tp) {
		mtx_lock(&ucom_mtx);
		ucom_close_refs++;
		mtx_unlock(&ucom_mtx);

		tty_lock(tp);

		ucom_close(tp);	/* close, if any */

		tty_rel_gone(tp);

		UCOM_MTX_LOCK(sc);
		/*
		 * make sure that read and write transfers are stopped
		 */
		if (sc->sc_callback->ucom_stop_read)
			(sc->sc_callback->ucom_stop_read) (sc);
		if (sc->sc_callback->ucom_stop_write)
			(sc->sc_callback->ucom_stop_write) (sc);
		UCOM_MTX_UNLOCK(sc);
	}
}