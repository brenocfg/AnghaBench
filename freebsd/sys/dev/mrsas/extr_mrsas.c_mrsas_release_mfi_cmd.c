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
typedef  scalar_t__ u_int32_t ;
struct mrsas_softc {int /*<<< orphan*/  mfi_cmd_pool_lock; int /*<<< orphan*/  mrsas_mfi_cmd_list_head; int /*<<< orphan*/  mpt_cmd_pool_lock; int /*<<< orphan*/  mrsas_mpt_cmd_list_head; struct mrsas_mpt_cmd** mpt_cmd_list; } ;
struct TYPE_3__ {int smid; } ;
struct TYPE_4__ {scalar_t__ frame_count; TYPE_1__ context; } ;
struct mrsas_mpt_cmd {TYPE_2__ cmd_id; int /*<<< orphan*/ * ccb_ptr; scalar_t__ sync_cmd_idx; scalar_t__ flags; struct mrsas_softc* sc; } ;
struct mrsas_mfi_cmd {TYPE_2__ cmd_id; int /*<<< orphan*/ * ccb_ptr; scalar_t__ sync_cmd_idx; scalar_t__ flags; struct mrsas_softc* sc; } ;

/* Variables and functions */
 scalar_t__ MRSAS_ULONG_MAX ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct mrsas_mpt_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 

void
mrsas_release_mfi_cmd(struct mrsas_mfi_cmd *cmd_mfi)
{
	struct mrsas_softc *sc = cmd_mfi->sc;
	struct mrsas_mpt_cmd *cmd_mpt;


	mtx_lock(&sc->mfi_cmd_pool_lock);
	/*
	 * Release the mpt command (if at all it is allocated
	 * associated with the mfi command
	 */
	if (cmd_mfi->cmd_id.context.smid) {
		mtx_lock(&sc->mpt_cmd_pool_lock);
		/* Get the mpt cmd from mfi cmd frame's smid value */
		cmd_mpt = sc->mpt_cmd_list[cmd_mfi->cmd_id.context.smid-1];
		cmd_mpt->flags = 0;
		cmd_mpt->sync_cmd_idx = (u_int32_t)MRSAS_ULONG_MAX;
		TAILQ_INSERT_HEAD(&(sc->mrsas_mpt_cmd_list_head), cmd_mpt, next);
		mtx_unlock(&sc->mpt_cmd_pool_lock);
	}
	/* Release the mfi command */
	cmd_mfi->ccb_ptr = NULL;
	cmd_mfi->cmd_id.frame_count = 0;
	TAILQ_INSERT_HEAD(&(sc->mrsas_mfi_cmd_list_head), cmd_mfi, next);
	mtx_unlock(&sc->mfi_cmd_pool_lock);

	return;
}