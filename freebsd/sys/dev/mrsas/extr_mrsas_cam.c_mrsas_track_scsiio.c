#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ target_id_t ;
struct mrsas_softc {int max_fw_cmds; int /*<<< orphan*/  mrsas_dev; struct mrsas_mpt_cmd** mpt_cmd_list; } ;
struct mrsas_mpt_cmd {TYPE_3__* ccb_ptr; } ;
struct TYPE_5__ {int target_id; } ;
struct TYPE_4__ {int bus_id; } ;
struct TYPE_6__ {TYPE_2__ ccb_h; TYPE_1__ cpi; } ;

/* Variables and functions */
 int FAIL ; 
 int MRSAS_MAX_PD ; 
 int SUCCESS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int
mrsas_track_scsiio(struct mrsas_softc *sc, target_id_t tgt_id, u_int32_t bus_id)
{
	int i;
	struct mrsas_mpt_cmd *mpt_cmd = NULL;

	for (i = 0 ; i < sc->max_fw_cmds; i++) {
		mpt_cmd = sc->mpt_cmd_list[i];

	/*
	 * Check if the target_id and bus_id is same as the timeout IO
	 */
	if (mpt_cmd->ccb_ptr) {
		/* bus_id = 1 denotes a VD */
		if (bus_id == 1)
			tgt_id = (mpt_cmd->ccb_ptr->ccb_h.target_id - (MRSAS_MAX_PD - 1));

			if (mpt_cmd->ccb_ptr->cpi.bus_id == bus_id &&
			    mpt_cmd->ccb_ptr->ccb_h.target_id == tgt_id) {
				device_printf(sc->mrsas_dev,
				    "IO commands pending to target id %d\n", tgt_id);
				return FAIL;
			}
		}
	}

	return SUCCESS;
}