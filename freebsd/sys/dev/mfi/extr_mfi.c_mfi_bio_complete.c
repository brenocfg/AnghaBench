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
struct mfi_softc {int /*<<< orphan*/  mfi_dev; } ;
struct mfi_frame_header {scalar_t__ cmd_status; scalar_t__ scsi_status; } ;
struct mfi_command {scalar_t__ cm_error; int /*<<< orphan*/  cm_sense; struct mfi_softc* cm_sc; TYPE_1__* cm_frame; struct bio* cm_private; } ;
struct bio {scalar_t__ bio_error; int /*<<< orphan*/  bio_flags; } ;
struct TYPE_2__ {struct mfi_frame_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ EIO ; 
 scalar_t__ MFI_STAT_OK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,struct mfi_command*,scalar_t__,...) ; 
 int /*<<< orphan*/  mfi_disk_complete (struct bio*) ; 
 int /*<<< orphan*/  mfi_print_sense (struct mfi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 

__attribute__((used)) static void
mfi_bio_complete(struct mfi_command *cm)
{
	struct bio *bio;
	struct mfi_frame_header *hdr;
	struct mfi_softc *sc;

	bio = cm->cm_private;
	hdr = &cm->cm_frame->header;
	sc = cm->cm_sc;

	if ((hdr->cmd_status != MFI_STAT_OK) || (hdr->scsi_status != 0)) {
		bio->bio_flags |= BIO_ERROR;
		bio->bio_error = EIO;
		device_printf(sc->mfi_dev, "I/O error, cmd=%p, status=%#x, "
		    "scsi_status=%#x\n", cm, hdr->cmd_status, hdr->scsi_status);
		mfi_print_sense(cm->cm_sc, cm->cm_sense);
	} else if (cm->cm_error != 0) {
		bio->bio_flags |= BIO_ERROR;
		bio->bio_error = cm->cm_error;
		device_printf(sc->mfi_dev, "I/O error, cmd=%p, error=%#x\n",
		    cm, cm->cm_error);
	}

	mfi_release_command(cm);
	mfi_disk_complete(bio);
}