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
struct mfi_softc {int (* mfi_check_clear_intr ) (struct mfi_softc*) ;int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_flags; scalar_t__ mfi_detaching; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_FLAGS_QFRZN ; 
 int /*<<< orphan*/  mfi_startio (struct mfi_softc*) ; 
 int /*<<< orphan*/  mfi_tbolt_complete_cmd (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mfi_softc*) ; 

void
mfi_intr_tbolt(void *arg)
{
	struct mfi_softc *sc = (struct mfi_softc *)arg;

	if (sc->mfi_check_clear_intr(sc) == 1) {
		return;
	}
	if (sc->mfi_detaching)
		return;
	mtx_lock(&sc->mfi_io_lock);
	mfi_tbolt_complete_cmd(sc);
	sc->mfi_flags &= ~MFI_FLAGS_QFRZN;
	mfi_startio(sc);
	mtx_unlock(&sc->mfi_io_lock);
	return;
}