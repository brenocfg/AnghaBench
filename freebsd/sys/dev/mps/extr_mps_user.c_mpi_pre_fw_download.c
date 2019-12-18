#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mps_usr_command {int req_len; int rpl_len; scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct mps_command {int /*<<< orphan*/  cm_flags; int /*<<< orphan*/  cm_data; scalar_t__ cm_req; } ;
struct TYPE_7__ {int MsgFlags; scalar_t__ TotalImageSize; int /*<<< orphan*/  SGL; } ;
struct TYPE_6__ {int DetailsLength; scalar_t__ ImageSize; scalar_t__ ImageOffset; scalar_t__ ContextSize; } ;
typedef  TYPE_1__ MPI2_FW_DOWNLOAD_TCSGE ;
typedef  TYPE_2__ MPI2_FW_DOWNLOAD_REQUEST ;
typedef  int /*<<< orphan*/  MPI2_FW_DOWNLOAD_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int EINVAL ; 
 int MPI2_FW_DOWNLOAD_MSGFLGS_LAST_SEGMENT ; 
 int /*<<< orphan*/  MPS_CM_FLAGS_DATAOUT ; 
 int MPS_SGC_SIZE ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mpi_init_sge (struct mps_command*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int mps_push_sge (struct mps_command*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpi_pre_fw_download(struct mps_command *cm, struct mps_usr_command *cmd)
{
	MPI2_FW_DOWNLOAD_REQUEST *req = (void *)cm->cm_req;
	MPI2_FW_DOWNLOAD_REPLY *rpl;
	MPI2_FW_DOWNLOAD_TCSGE tc;
	int error;

	/*
	 * This code assumes there is room in the request's SGL for
	 * the TransactionContext plus at least a SGL chain element.
	 */
	CTASSERT(sizeof req->SGL >= sizeof tc + MPS_SGC_SIZE);

	if (cmd->req_len != sizeof *req)
		return (EINVAL);
	if (cmd->rpl_len != sizeof *rpl)
		return (EINVAL);

	if (cmd->len == 0)
		return (EINVAL);

	error = copyin(cmd->buf, cm->cm_data, cmd->len);
	if (error != 0)
		return (error);

	mpi_init_sge(cm, req, &req->SGL);
	bzero(&tc, sizeof tc);

	/*
	 * For now, the F/W image must be provided in a single request.
	 */
	if ((req->MsgFlags & MPI2_FW_DOWNLOAD_MSGFLGS_LAST_SEGMENT) == 0)
		return (EINVAL);
	if (req->TotalImageSize != cmd->len)
		return (EINVAL);

	/*
	 * The value of the first two elements is specified in the
	 * Fusion-MPT Message Passing Interface document.
	 */
	tc.ContextSize = 0;
	tc.DetailsLength = 12;
	tc.ImageOffset = 0;
	tc.ImageSize = cmd->len;

	cm->cm_flags |= MPS_CM_FLAGS_DATAOUT;

	return (mps_push_sge(cm, &tc, sizeof tc, 0));
}