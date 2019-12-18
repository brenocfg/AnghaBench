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
struct mfi_softc {scalar_t__ MFA_enabled; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_command {int cm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MFI_ON_MFIQ_BUSY ; 
 int /*<<< orphan*/  mfi_remove_busy (struct mfi_command*) ; 
 int mfi_std_send_frame (struct mfi_softc*,struct mfi_command*) ; 
 int mfi_tbolt_send_frame (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mfi_send_frame(struct mfi_softc *sc, struct mfi_command *cm)
{
	int error;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	if (sc->MFA_enabled)
		error = mfi_tbolt_send_frame(sc, cm);
	else
		error = mfi_std_send_frame(sc, cm);

	if (error != 0 && (cm->cm_flags & MFI_ON_MFIQ_BUSY) != 0)
		mfi_remove_busy(cm);

	return (error);
}