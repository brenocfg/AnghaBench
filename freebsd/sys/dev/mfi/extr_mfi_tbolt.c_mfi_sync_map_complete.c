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
struct mfi_softc {int /*<<< orphan*/ * mfi_map_sync_cm; scalar_t__ cm_map_abort; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_frame_header {scalar_t__ cmd_status; } ;
struct mfi_command {int /*<<< orphan*/  cm_data; TYPE_1__* cm_frame; struct mfi_softc* cm_sc; } ;
struct TYPE_2__ {struct mfi_frame_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ MFI_STAT_INVALID_STATUS ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_queue_map_sync (struct mfi_softc*) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
mfi_sync_map_complete(struct mfi_command *cm)
{
	struct mfi_frame_header *hdr;
	struct mfi_softc *sc;
	int aborted = 0;

	sc = cm->cm_sc;
	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	hdr = &cm->cm_frame->header;

	if (sc->mfi_map_sync_cm == NULL)
		return;

	if (sc->cm_map_abort ||
	    hdr->cmd_status == MFI_STAT_INVALID_STATUS) {
		sc->cm_map_abort = 0;
		aborted = 1;
	}

	free(cm->cm_data, M_MFIBUF);
	wakeup(&sc->mfi_map_sync_cm);
	sc->mfi_map_sync_cm = NULL;
	mfi_release_command(cm);

	/* set it up again so the driver can catch more events */
	if (!aborted)
		mfi_queue_map_sync(sc);
}