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
struct mfi_softc {int mfi_flags; int /*<<< orphan*/  mfi_ich; int /*<<< orphan*/  mfi_config_lock; int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  (* mfi_enable_intr ) (struct mfi_softc*) ;} ;

/* Variables and functions */
 int MFI_FLAGS_SKINNY ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfi_ldprobe (struct mfi_softc*) ; 
 int /*<<< orphan*/  mfi_syspdprobe (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mfi_softc*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mfi_startup(void *arg)
{
	struct mfi_softc *sc;

	sc = (struct mfi_softc *)arg;

	sc->mfi_enable_intr(sc);
	sx_xlock(&sc->mfi_config_lock);
	mtx_lock(&sc->mfi_io_lock);
	mfi_ldprobe(sc);
	if (sc->mfi_flags & MFI_FLAGS_SKINNY)
	    mfi_syspdprobe(sc);
	mtx_unlock(&sc->mfi_io_lock);
	sx_xunlock(&sc->mfi_config_lock);

	config_intrhook_disestablish(&sc->mfi_ich);
}