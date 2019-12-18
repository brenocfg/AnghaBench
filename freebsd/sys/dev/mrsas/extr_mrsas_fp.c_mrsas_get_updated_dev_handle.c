#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct mrsas_softc {int map_id; int /*<<< orphan*/ ** ld_drv_map; } ;
struct IO_REQUEST_INFO {int /*<<< orphan*/  pdInterface; } ;
struct TYPE_4__ {int /*<<< orphan*/ * scsi_pending_cmds; } ;
typedef  TYPE_1__* PLD_LOAD_BALANCE_INFO ;
typedef  int /*<<< orphan*/  MR_DRV_RAID_MAP_ALL ;

/* Variables and functions */
 int /*<<< orphan*/  MR_PdDevHandleGet (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MR_PdInterfaceTypeGet (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrsas_atomic_inc (int /*<<< orphan*/ *) ; 
 size_t mrsas_get_best_arm_pd (struct mrsas_softc*,TYPE_1__*,struct IO_REQUEST_INFO*) ; 

u_int16_t 
mrsas_get_updated_dev_handle(struct mrsas_softc *sc,
    PLD_LOAD_BALANCE_INFO lbInfo, struct IO_REQUEST_INFO *io_info)
{
	u_int8_t arm_pd;
	u_int16_t devHandle;
	MR_DRV_RAID_MAP_ALL *drv_map;

	drv_map = sc->ld_drv_map[(sc->map_id & 1)];

	/* get best new arm */
	arm_pd = mrsas_get_best_arm_pd(sc, lbInfo, io_info);
	devHandle = MR_PdDevHandleGet(arm_pd, drv_map);
	io_info->pdInterface = MR_PdInterfaceTypeGet(arm_pd, drv_map);
	mrsas_atomic_inc(&lbInfo->scsi_pending_cmds[arm_pd]);

	return devHandle;
}