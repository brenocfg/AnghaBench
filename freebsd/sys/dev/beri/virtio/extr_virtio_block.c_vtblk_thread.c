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
struct beri_vtblk_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int PCATCH ; 
 int PZERO ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int msleep (struct beri_vtblk_softc*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtblk_notify (struct beri_vtblk_softc*) ; 

__attribute__((used)) static void
vtblk_thread(void *arg)
{
	struct beri_vtblk_softc *sc;
	int err;

	sc = arg;

	sx_xlock(&sc->sc_mtx);
	for (;;) {
		err = msleep(sc, &sc->sc_mtx, PCATCH | PZERO, "prd", hz);
		vtblk_notify(sc);
	}
	sx_xunlock(&sc->sc_mtx);

	kthread_exit();
}