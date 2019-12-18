#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int RequestFlags; scalar_t__ SMID; } ;
union mfi_mpi2_request_descriptor {TYPE_1__ header; } ;
typedef  scalar_t__ uint16_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_dev; } ;
struct mfi_command {scalar_t__ cm_extra_frames; } ;

/* Variables and functions */
 int MFI_REQ_DESCRIPT_FLAGS_TYPE_SHIFT ; 
 int MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO ; 
 int /*<<< orphan*/  bzero (union mfi_mpi2_request_descriptor*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mfi_build_mpt_pass_thru (struct mfi_softc*,struct mfi_command*) ; 
 union mfi_mpi2_request_descriptor* mfi_tbolt_get_request_descriptor (struct mfi_softc*,scalar_t__) ; 

union mfi_mpi2_request_descriptor *
mfi_tbolt_build_mpt_cmd(struct mfi_softc *sc, struct mfi_command *cmd)
{
	union mfi_mpi2_request_descriptor *req_desc = NULL;
	uint16_t index;
	if (mfi_build_mpt_pass_thru(sc, cmd)) {
		device_printf(sc->mfi_dev, "Couldn't build MFI pass thru "
		    "cmd\n");
		return NULL;
	}
	/* For fusion the frame_count variable is used for SMID */
	index = cmd->cm_extra_frames;

	req_desc = mfi_tbolt_get_request_descriptor(sc, index - 1);
	if (req_desc == NULL)
		return NULL;

	bzero(req_desc, sizeof(*req_desc));
	req_desc->header.RequestFlags = (MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO <<
	    MFI_REQ_DESCRIPT_FLAGS_TYPE_SHIFT);
	req_desc->header.SMID = index;
	return req_desc;
}