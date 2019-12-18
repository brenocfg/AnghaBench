#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct mfi_softc {int dummy; } ;
struct TYPE_11__ {int TargetID; int RegLockLength; int /*<<< orphan*/  timeoutValue; scalar_t__ regLockFlags; scalar_t__ exStatus; scalar_t__ Status; } ;
struct mfi_mpi2_request_raid_scsi_io {int DevHandle; int IoFlags; int DataLength; TYPE_4__ RaidContext; int /*<<< orphan*/  Function; } ;
struct mfi_command {TYPE_7__* cm_frame; } ;
struct mfi_cmd_tbolt {TYPE_3__* request_desc; struct mfi_mpi2_request_raid_scsi_io* io_request; } ;
struct IO_REQUEST_INFO {int ldStartBlock; scalar_t__ numBlocks; int ldTgtId; int isRead; } ;
struct TYPE_12__ {int target_id; scalar_t__ data_len; } ;
struct TYPE_13__ {int lba_lo; int lba_hi; TYPE_5__ header; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_14__ {TYPE_6__ io; TYPE_1__ header; } ;
struct TYPE_9__ {int RequestFlags; } ;
struct TYPE_10__ {TYPE_2__ header; } ;

/* Variables and functions */
 int MFI_FRAME_DIR_READ ; 
 int /*<<< orphan*/  MFI_FUSION_FP_DEFAULT_TIMEOUT ; 
 int MFI_REQ_DESCRIPT_FLAGS_LD_IO ; 
 int MFI_REQ_DESCRIPT_FLAGS_TYPE_SHIFT ; 
 int MFI_SECTOR_LEN ; 
 int /*<<< orphan*/  MPI2_FUNCTION_LD_IO_REQUEST ; 
 int /*<<< orphan*/  memset (struct IO_REQUEST_INFO*,int /*<<< orphan*/ ,int) ; 

void
mfi_tbolt_build_ldio(struct mfi_softc *sc, struct mfi_command *mfi_cmd,
    struct mfi_cmd_tbolt *cmd)
{
	uint32_t start_lba_lo = 0, start_lba_hi = 0, device_id;
	struct mfi_mpi2_request_raid_scsi_io	*io_request;
	struct IO_REQUEST_INFO io_info;

	device_id = mfi_cmd->cm_frame->io.header.target_id;
	io_request = cmd->io_request;
	io_request->RaidContext.TargetID = device_id;
	io_request->RaidContext.Status = 0;
	io_request->RaidContext.exStatus = 0;
	io_request->RaidContext.regLockFlags = 0;

	start_lba_lo = mfi_cmd->cm_frame->io.lba_lo;
	start_lba_hi = mfi_cmd->cm_frame->io.lba_hi;

	memset(&io_info, 0, sizeof(struct IO_REQUEST_INFO));
	io_info.ldStartBlock = ((uint64_t)start_lba_hi << 32) | start_lba_lo;
	io_info.numBlocks = mfi_cmd->cm_frame->io.header.data_len;
	io_info.ldTgtId = device_id;
	if ((mfi_cmd->cm_frame->header.flags & MFI_FRAME_DIR_READ) ==
	    MFI_FRAME_DIR_READ)
		io_info.isRead = 1;

	io_request->RaidContext.timeoutValue
		= MFI_FUSION_FP_DEFAULT_TIMEOUT;
	io_request->Function = MPI2_FUNCTION_LD_IO_REQUEST;
	io_request->DevHandle = device_id;
	cmd->request_desc->header.RequestFlags
		= (MFI_REQ_DESCRIPT_FLAGS_LD_IO
		   << MFI_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
	if ((io_request->IoFlags == 6) && (io_info.numBlocks == 0))
		io_request->RaidContext.RegLockLength = 0x100;
	io_request->DataLength = mfi_cmd->cm_frame->io.header.data_len
	    * MFI_SECTOR_LEN;
}