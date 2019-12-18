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
struct mrsas_softc {int /*<<< orphan*/  mpt_cmd_pool_lock; int /*<<< orphan*/  mrsas_mpt_cmd_list_head; } ;
struct mrsas_mpt_cmd {int /*<<< orphan*/ * ccb_ptr; scalar_t__ load_balance; scalar_t__ error_code; scalar_t__ flags; scalar_t__ length; int /*<<< orphan*/ * data; scalar_t__ io_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRSAS_MPI2_RAID_DEFAULT_IO_FRAME_SIZE ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct mrsas_mpt_cmd* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mrsas_mpt_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 

struct mrsas_mpt_cmd *
mrsas_get_mpt_cmd(struct mrsas_softc *sc)
{
	struct mrsas_mpt_cmd *cmd = NULL;

	mtx_lock(&sc->mpt_cmd_pool_lock);
	if (!TAILQ_EMPTY(&sc->mrsas_mpt_cmd_list_head)) {
		cmd = TAILQ_FIRST(&sc->mrsas_mpt_cmd_list_head);
		TAILQ_REMOVE(&sc->mrsas_mpt_cmd_list_head, cmd, next);
	} else {
		goto out;
	}

	memset((uint8_t *)cmd->io_request, 0, MRSAS_MPI2_RAID_DEFAULT_IO_FRAME_SIZE);
	cmd->data = NULL;
	cmd->length = 0;
	cmd->flags = 0;
	cmd->error_code = 0;
	cmd->load_balance = 0;
	cmd->ccb_ptr = NULL;
out:
	mtx_unlock(&sc->mpt_cmd_pool_lock);
	return cmd;
}