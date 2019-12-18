#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ccb_scsiio {int /*<<< orphan*/  cdb_len; } ;
struct ccb_hdr {int /*<<< orphan*/  target_id; } ;
union ccb {struct ccb_scsiio csio; struct ccb_hdr ccb_h; } ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct mrsas_softc {int max_num_sge; int /*<<< orphan*/  mrsas_dev; scalar_t__ is_aero; scalar_t__ is_ventura; } ;
struct mrsas_mpt_cmd {int sge_count; int /*<<< orphan*/  length; TYPE_4__* io_request; } ;
struct TYPE_7__ {int numSGE; scalar_t__ numSGEExt; scalar_t__ exStatus; scalar_t__ status; int /*<<< orphan*/  VirtualDiskTgtId; } ;
struct TYPE_6__ {int numSGE; } ;
struct TYPE_8__ {TYPE_2__ raid_context; TYPE_1__ raid_context_g35; } ;
struct TYPE_9__ {TYPE_3__ RaidContext; int /*<<< orphan*/  DataLength; int /*<<< orphan*/  IoFlags; } ;
typedef  TYPE_4__ MRSAS_RAID_SCSI_IO_REQUEST ;

/* Variables and functions */
 int FAIL ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mrsas_map_request (struct mrsas_softc*,struct mrsas_mpt_cmd*,union ccb*) ; 
 scalar_t__ mrsas_setup_io (struct mrsas_softc*,struct mrsas_mpt_cmd*,union ccb*,int /*<<< orphan*/ ,TYPE_4__*) ; 

int
mrsas_build_ldio_rw(struct mrsas_softc *sc, struct mrsas_mpt_cmd *cmd,
    union ccb *ccb)
{
	struct ccb_hdr *ccb_h = &(ccb->ccb_h);
	struct ccb_scsiio *csio = &(ccb->csio);
	u_int32_t device_id;
	MRSAS_RAID_SCSI_IO_REQUEST *io_request;

	device_id = ccb_h->target_id;

	io_request = cmd->io_request;
	io_request->RaidContext.raid_context.VirtualDiskTgtId = device_id;
	io_request->RaidContext.raid_context.status = 0;
	io_request->RaidContext.raid_context.exStatus = 0;

	/* just the cdb len, other flags zero, and ORed-in later for FP */
	io_request->IoFlags = csio->cdb_len;

	if (mrsas_setup_io(sc, cmd, ccb, device_id, io_request) != SUCCESS)
		device_printf(sc->mrsas_dev, "Build ldio or fpio error\n");

	io_request->DataLength = cmd->length;

	if (mrsas_map_request(sc, cmd, ccb) == SUCCESS) {
		if (cmd->sge_count > sc->max_num_sge) {
			device_printf(sc->mrsas_dev, "Error: sge_count (0x%x) exceeds"
			    "max (0x%x) allowed\n", cmd->sge_count, sc->max_num_sge);
			return (FAIL);
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
		return (FAIL);
	}
	return (0);
}