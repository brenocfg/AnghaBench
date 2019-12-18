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
struct mfi_softc {int /*<<< orphan*/  mfi_cmd_tbolt_tqh; int /*<<< orphan*/  mfi_max_fw_cmds; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_command {scalar_t__ cm_extra_frames; int /*<<< orphan*/  cm_flags; } ;
struct mfi_cmd_tbolt {int /*<<< orphan*/  sync_cmd_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MFI_CMD_TBOLT ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mfi_cmd_tbolt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

void
mfi_tbolt_return_cmd(struct mfi_softc *sc, struct mfi_cmd_tbolt *tbolt_cmd,
    struct mfi_command *mfi_cmd)
{
	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	mfi_cmd->cm_flags &= ~MFI_CMD_TBOLT;
	mfi_cmd->cm_extra_frames = 0;
	tbolt_cmd->sync_cmd_idx = sc->mfi_max_fw_cmds;

	TAILQ_INSERT_TAIL(&sc->mfi_cmd_tbolt_tqh, tbolt_cmd, next);
}