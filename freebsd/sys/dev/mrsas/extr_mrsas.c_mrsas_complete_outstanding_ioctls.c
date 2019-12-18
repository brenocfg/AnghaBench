#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct mrsas_softc {scalar_t__ msix_vectors; int max_fw_cmds; struct mrsas_mfi_cmd** mfi_cmd_list; struct mrsas_mpt_cmd** mpt_cmd_list; } ;
struct mrsas_mpt_cmd {int sync_cmd_idx; TYPE_5__* io_request; } ;
struct mrsas_mfi_cmd {TYPE_2__* frame; scalar_t__ sync_cmd; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct TYPE_9__ {TYPE_3__ raid_context; } ;
struct TYPE_10__ {TYPE_4__ RaidContext; } ;
struct TYPE_6__ {scalar_t__ cmd; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ MFI_CMD_ABORT ; 
 scalar_t__ MRSAS_ULONG_MAX ; 
 int /*<<< orphan*/  mrsas_complete_mptmfi_passthru (struct mrsas_softc*,struct mrsas_mfi_cmd*,int /*<<< orphan*/ ) ; 

void 
mrsas_complete_outstanding_ioctls(struct mrsas_softc *sc)
{
	int i;
	struct mrsas_mpt_cmd *cmd_mpt;
	struct mrsas_mfi_cmd *cmd_mfi;
	u_int32_t count, MSIxIndex;

	count = sc->msix_vectors > 0 ? sc->msix_vectors : 1;
	for (i = 0; i < sc->max_fw_cmds; i++) {
		cmd_mpt = sc->mpt_cmd_list[i];

		if (cmd_mpt->sync_cmd_idx != (u_int32_t)MRSAS_ULONG_MAX) {
			cmd_mfi = sc->mfi_cmd_list[cmd_mpt->sync_cmd_idx];
			if (cmd_mfi->sync_cmd && cmd_mfi->frame->hdr.cmd != MFI_CMD_ABORT) {
				for (MSIxIndex = 0; MSIxIndex < count; MSIxIndex++)
					mrsas_complete_mptmfi_passthru(sc, cmd_mfi,
					    cmd_mpt->io_request->RaidContext.raid_context.status);
			}
		}
	}
}