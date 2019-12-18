#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mfi_softc {int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/  (* mfi_issue_cmd ) (struct mfi_softc*,int /*<<< orphan*/ ,int) ;} ;
struct mfi_frame_header {scalar_t__ cmd_status; int /*<<< orphan*/  flags; } ;
struct mfi_command {int cm_flags; int cm_extra_frames; TYPE_2__* cm_frame; int /*<<< orphan*/  cm_frame_busaddr; int /*<<< orphan*/  cm_timestamp; } ;
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {TYPE_1__ dcmd; struct mfi_frame_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int MFI_CMD_POLLED ; 
 int /*<<< orphan*/  MFI_FRAME_DONT_POST_IN_REPLY_QUEUE ; 
 scalar_t__ MFI_STAT_INVALID_STATUS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,struct mfi_frame_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_enqueue_busy (struct mfi_command*) ; 
 int mfi_polled_cmd_timeout ; 
 int /*<<< orphan*/  stub1 (struct mfi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static int
mfi_std_send_frame(struct mfi_softc *sc, struct mfi_command *cm)
{
	struct mfi_frame_header *hdr;
	int tm = mfi_polled_cmd_timeout * 1000;

	hdr = &cm->cm_frame->header;

	if ((cm->cm_flags & MFI_CMD_POLLED) == 0) {
		cm->cm_timestamp = time_uptime;
		mfi_enqueue_busy(cm);
	} else {
		hdr->cmd_status = MFI_STAT_INVALID_STATUS;
		hdr->flags |= MFI_FRAME_DONT_POST_IN_REPLY_QUEUE;
	}

	/*
	 * The bus address of the command is aligned on a 64 byte boundary,
	 * leaving the least 6 bits as zero.  For whatever reason, the
	 * hardware wants the address shifted right by three, leaving just
	 * 3 zero bits.  These three bits are then used as a prefetching
	 * hint for the hardware to predict how many frames need to be
	 * fetched across the bus.  If a command has more than 8 frames
	 * then the 3 bits are set to 0x7 and the firmware uses other
	 * information in the command to determine the total amount to fetch.
	 * However, FreeBSD doesn't support I/O larger than 128K, so 8 frames
	 * is enough for both 32bit and 64bit systems.
	 */
	if (cm->cm_extra_frames > 7)
		cm->cm_extra_frames = 7;

	sc->mfi_issue_cmd(sc, cm->cm_frame_busaddr, cm->cm_extra_frames);

	if ((cm->cm_flags & MFI_CMD_POLLED) == 0)
		return (0);

	/* This is a polled command, so busy-wait for it to complete. */
	while (hdr->cmd_status == MFI_STAT_INVALID_STATUS) {
		DELAY(1000);
		tm -= 1;
		if (tm <= 0)
			break;
	}

	if (hdr->cmd_status == MFI_STAT_INVALID_STATUS) {
		device_printf(sc->mfi_dev, "Frame %p timed out "
		    "command 0x%X\n", hdr, cm->cm_frame->dcmd.opcode);
		return (ETIMEDOUT);
	}

	return (0);
}