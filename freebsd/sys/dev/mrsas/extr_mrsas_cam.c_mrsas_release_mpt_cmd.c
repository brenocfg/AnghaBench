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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u_int32_t ;
struct mrsas_softc {int /*<<< orphan*/  mpt_cmd_pool_lock; int /*<<< orphan*/  mrsas_mpt_cmd_list_head; } ;
struct mrsas_mpt_cmd {scalar_t__ io_request; scalar_t__ cmd_completed; int /*<<< orphan*/ * peer_cmd; scalar_t__ sync_cmd_idx; int /*<<< orphan*/  r1_alt_dev_handle; struct mrsas_softc* sc; } ;
typedef  int /*<<< orphan*/  MRSAS_RAID_SCSI_IO_REQUEST ;

/* Variables and functions */
 scalar_t__ MRSAS_ULONG_MAX ; 
 int /*<<< orphan*/  MR_DEVHANDLE_INVALID ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct mrsas_mpt_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 

void
mrsas_release_mpt_cmd(struct mrsas_mpt_cmd *cmd)
{
	struct mrsas_softc *sc = cmd->sc;

	mtx_lock(&sc->mpt_cmd_pool_lock);
	cmd->r1_alt_dev_handle = MR_DEVHANDLE_INVALID;
	cmd->sync_cmd_idx = (u_int32_t)MRSAS_ULONG_MAX;
	cmd->peer_cmd = NULL;
	cmd->cmd_completed = 0;
	memset((uint8_t *)cmd->io_request, 0,
		sizeof(MRSAS_RAID_SCSI_IO_REQUEST));
	TAILQ_INSERT_HEAD(&(sc->mrsas_mpt_cmd_list_head), cmd, next);
	mtx_unlock(&sc->mpt_cmd_pool_lock);

	return;
}