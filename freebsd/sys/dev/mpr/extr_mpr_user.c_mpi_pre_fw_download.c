#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpr_usr_command {int req_len; int rpl_len; scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct mpr_command {int /*<<< orphan*/  cm_flags; int /*<<< orphan*/  cm_data; scalar_t__ cm_req; } ;
struct TYPE_3__ {int MsgFlags; scalar_t__ TotalImageSize; scalar_t__ ImageSize; int /*<<< orphan*/  SGL; scalar_t__ ImageOffset; } ;
typedef  int /*<<< orphan*/  MPI2_FW_DOWNLOAD_REPLY ;
typedef  TYPE_1__ MPI25_FW_DOWNLOAD_REQUEST ;

/* Variables and functions */
 int EINVAL ; 
 int MPI2_FW_DOWNLOAD_MSGFLGS_LAST_SEGMENT ; 
 int /*<<< orphan*/  MPR_CM_FLAGS_DATAOUT ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mpr_init_sge (struct mpr_command*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mpr_push_ieee_sge (struct mpr_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpi_pre_fw_download(struct mpr_command *cm, struct mpr_usr_command *cmd)
{
	MPI25_FW_DOWNLOAD_REQUEST *req = (void *)cm->cm_req;
	MPI2_FW_DOWNLOAD_REPLY *rpl;
	int error;

	if (cmd->req_len != sizeof *req)
		return (EINVAL);
	if (cmd->rpl_len != sizeof *rpl)
		return (EINVAL);

	if (cmd->len == 0)
		return (EINVAL);

	error = copyin(cmd->buf, cm->cm_data, cmd->len);
	if (error != 0)
		return (error);

	mpr_init_sge(cm, req, &req->SGL);

	/*
	 * For now, the F/W image must be provided in a single request.
	 */
	if ((req->MsgFlags & MPI2_FW_DOWNLOAD_MSGFLGS_LAST_SEGMENT) == 0)
		return (EINVAL);
	if (req->TotalImageSize != cmd->len)
		return (EINVAL);

	req->ImageOffset = 0;
	req->ImageSize = cmd->len;

	cm->cm_flags |= MPR_CM_FLAGS_DATAOUT;

	return (mpr_push_ieee_sge(cm, &req->SGL, 0));
}