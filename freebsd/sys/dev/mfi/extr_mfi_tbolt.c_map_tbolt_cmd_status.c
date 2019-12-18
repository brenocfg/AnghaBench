#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct mfi_command {int cm_error; TYPE_4__* cm_frame; } ;
struct TYPE_6__ {int cmd_status; int scsi_status; } ;
struct TYPE_7__ {TYPE_2__ header; } ;
struct TYPE_5__ {int cmd_status; int scsi_status; } ;
struct TYPE_8__ {TYPE_3__ dcmd; TYPE_1__ header; } ;

/* Variables and functions */
#define  MFI_STAT_DEVICE_NOT_FOUND 133 
#define  MFI_STAT_LD_INIT_IN_PROGRESS 132 
#define  MFI_STAT_LD_OFFLINE 131 
#define  MFI_STAT_OK 130 
#define  MFI_STAT_SCSI_DONE_WITH_ERROR 129 
#define  MFI_STAT_SCSI_IO_FAILED 128 

void
map_tbolt_cmd_status(struct mfi_command *mfi_cmd, uint8_t status,
    uint8_t ext_status)
{
	switch (status) {
	case MFI_STAT_OK:
		mfi_cmd->cm_frame->header.cmd_status = MFI_STAT_OK;
		mfi_cmd->cm_frame->dcmd.header.cmd_status = MFI_STAT_OK;
		mfi_cmd->cm_error = MFI_STAT_OK;
		break;

	case MFI_STAT_SCSI_IO_FAILED:
	case MFI_STAT_LD_INIT_IN_PROGRESS:
		mfi_cmd->cm_frame->header.cmd_status = status;
		mfi_cmd->cm_frame->header.scsi_status = ext_status;
		mfi_cmd->cm_frame->dcmd.header.cmd_status = status;
		mfi_cmd->cm_frame->dcmd.header.scsi_status
		    = ext_status;
		break;

	case MFI_STAT_SCSI_DONE_WITH_ERROR:
		mfi_cmd->cm_frame->header.cmd_status = ext_status;
		mfi_cmd->cm_frame->dcmd.header.cmd_status = ext_status;
		break;

	case MFI_STAT_LD_OFFLINE:
	case MFI_STAT_DEVICE_NOT_FOUND:
		mfi_cmd->cm_frame->header.cmd_status = status;
		mfi_cmd->cm_frame->dcmd.header.cmd_status = status;
		break;

	default:
		mfi_cmd->cm_frame->header.cmd_status = status;
		mfi_cmd->cm_frame->dcmd.header.cmd_status = status;
		break;
	}
}