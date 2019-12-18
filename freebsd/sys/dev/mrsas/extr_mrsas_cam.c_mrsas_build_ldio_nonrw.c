#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ccb_hdr {int target_lun; void* target_id; } ;
union ccb {struct ccb_hdr ccb_h; } ;
typedef  scalar_t__ uint8_t ;
typedef  void* u_int32_t ;
struct mrsas_softc {int map_id; int max_num_sge; int /*<<< orphan*/  mrsas_dev; scalar_t__ is_aero; scalar_t__ is_ventura; int /*<<< orphan*/ ** ld_drv_map; } ;
struct mrsas_mpt_cmd {int sge_count; int /*<<< orphan*/  length; TYPE_3__* request_desc; int /*<<< orphan*/  tmCapable; TYPE_8__* io_request; } ;
struct TYPE_15__ {int numSGE; scalar_t__ numSGEExt; void* VirtualDiskTgtId; } ;
struct TYPE_13__ {int numSGE; } ;
struct TYPE_14__ {TYPE_6__ raid_context; TYPE_4__ raid_context_g35; } ;
struct TYPE_17__ {int* LUN; TYPE_5__ RaidContext; int /*<<< orphan*/  DataLength; void* DevHandle; int /*<<< orphan*/  Function; } ;
struct TYPE_10__ {int /*<<< orphan*/  tmCapable; } ;
struct TYPE_16__ {TYPE_1__ capability; } ;
struct TYPE_11__ {int RequestFlags; } ;
struct TYPE_12__ {TYPE_2__ SCSIIO; } ;
typedef  TYPE_6__ RAID_CONTEXT ;
typedef  TYPE_7__ MR_LD_RAID ;
typedef  int /*<<< orphan*/  MR_DRV_RAID_MAP_ALL ;
typedef  TYPE_8__ MRSAS_RAID_SCSI_IO_REQUEST ;

/* Variables and functions */
 int MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO ; 
 int /*<<< orphan*/  MRSAS_MPI2_FUNCTION_LD_IO_REQUEST ; 
 int MRSAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT ; 
 TYPE_7__* MR_LdRaidGet (void*,int /*<<< orphan*/ *) ; 
 void* MR_TargetIdToLdGet (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mrsas_map_request (struct mrsas_softc*,struct mrsas_mpt_cmd*,union ccb*) ; 

int
mrsas_build_ldio_nonrw(struct mrsas_softc *sc, struct mrsas_mpt_cmd *cmd,
    union ccb *ccb)
{
	struct ccb_hdr *ccb_h = &(ccb->ccb_h);
	u_int32_t device_id, ld;
	MR_DRV_RAID_MAP_ALL *map_ptr;
	MR_LD_RAID *raid;
	RAID_CONTEXT *pRAID_Context;
	MRSAS_RAID_SCSI_IO_REQUEST *io_request;

	io_request = cmd->io_request;
	device_id = ccb_h->target_id;

	map_ptr = sc->ld_drv_map[(sc->map_id & 1)];
	ld = MR_TargetIdToLdGet(device_id, map_ptr);
	raid = MR_LdRaidGet(ld, map_ptr);
	/* get RAID_Context pointer */
	pRAID_Context = &io_request->RaidContext.raid_context;
	/* Store the TM capability value in cmd */
	cmd->tmCapable = raid->capability.tmCapable;

	/* FW path for LD Non-RW (SCSI management commands) */
	io_request->Function = MRSAS_MPI2_FUNCTION_LD_IO_REQUEST;
	io_request->DevHandle = device_id;
	cmd->request_desc->SCSIIO.RequestFlags =
	    (MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO <<
	    MRSAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);

	io_request->RaidContext.raid_context.VirtualDiskTgtId = device_id;
	io_request->LUN[1] = ccb_h->target_lun & 0xF;
	io_request->DataLength = cmd->length;

	if (mrsas_map_request(sc, cmd, ccb) == SUCCESS) {
		if (cmd->sge_count > sc->max_num_sge) {
			device_printf(sc->mrsas_dev, "Error: sge_count (0x%x) exceeds"
			    "max (0x%x) allowed\n", cmd->sge_count, sc->max_num_sge);
			return (1);
		}
		if (sc->is_ventura || sc->is_aero)
			io_request->RaidContext.raid_context_g35.numSGE = cmd->sge_count;
		else {
			/*
			 * numSGE store lower 8 bit of sge_count. numSGEExt store
			 * higher 8 bit of sge_count
			 */
			io_request->RaidContext.raid_context.numSGE = cmd->sge_count;
			io_request->RaidContext.raid_context.numSGEExt = (uint8_t)(cmd->sge_count >> 8);
		}
	} else {
		device_printf(sc->mrsas_dev, "Data map/load failed.\n");
		return (1);
	}
	return (0);
}