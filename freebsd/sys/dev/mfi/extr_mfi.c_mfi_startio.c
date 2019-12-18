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
struct mfi_softc {int mfi_flags; int /*<<< orphan*/  mfi_dev; struct mfi_command* (* mfi_cam_start ) (struct ccb_hdr*) ;int /*<<< orphan*/  mfi_cam_ccbq; } ;
struct mfi_command {int dummy; } ;
struct ccb_hdr {int dummy; } ;

/* Variables and functions */
 int MFI_FLAGS_QFRZN ; 
 struct ccb_hdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct mfi_command* mfi_bio_command (struct mfi_softc*) ; 
 struct mfi_command* mfi_dequeue_ready (struct mfi_softc*) ; 
 scalar_t__ mfi_mapcmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_requeue_ready (struct mfi_command*) ; 
 struct mfi_command* stub1 (struct ccb_hdr*) ; 

void
mfi_startio(struct mfi_softc *sc)
{
	struct mfi_command *cm;
	struct ccb_hdr *ccbh;

	for (;;) {
		/* Don't bother if we're short on resources */
		if (sc->mfi_flags & MFI_FLAGS_QFRZN)
			break;

		/* Try a command that has already been prepared */
		cm = mfi_dequeue_ready(sc);

		if (cm == NULL) {
			if ((ccbh = TAILQ_FIRST(&sc->mfi_cam_ccbq)) != NULL)
				cm = sc->mfi_cam_start(ccbh);
		}

		/* Nope, so look for work on the bioq */
		if (cm == NULL)
			cm = mfi_bio_command(sc);

		/* No work available, so exit */
		if (cm == NULL)
			break;

		/* Send the command to the controller */
		if (mfi_mapcmd(sc, cm) != 0) {
			device_printf(sc->mfi_dev, "Failed to startio\n");
			mfi_requeue_ready(cm);
			break;
		}
	}
}