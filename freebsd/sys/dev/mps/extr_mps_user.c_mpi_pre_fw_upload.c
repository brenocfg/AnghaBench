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
struct mps_usr_command {int req_len; int rpl_len; int /*<<< orphan*/  len; } ;
struct mps_command {int /*<<< orphan*/  cm_flags; scalar_t__ cm_req; } ;
struct TYPE_7__ {int /*<<< orphan*/  SGL; } ;
struct TYPE_6__ {int DetailsLength; int /*<<< orphan*/  ImageSize; scalar_t__ ImageOffset; scalar_t__ ContextSize; } ;
typedef  TYPE_1__ MPI2_FW_UPLOAD_TCSGE ;
typedef  TYPE_2__ MPI2_FW_UPLOAD_REQUEST ;
typedef  int /*<<< orphan*/  MPI2_FW_UPLOAD_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MPS_CM_FLAGS_DATAIN ; 
 int MPS_SGC_SIZE ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mpi_init_sge (struct mps_command*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int mps_push_sge (struct mps_command*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpi_pre_fw_upload(struct mps_command *cm, struct mps_usr_command *cmd)
{
	MPI2_FW_UPLOAD_REQUEST *req = (void *)cm->cm_req;
	MPI2_FW_UPLOAD_REPLY *rpl;
	MPI2_FW_UPLOAD_TCSGE tc;

	/*
	 * This code assumes there is room in the request's SGL for
	 * the TransactionContext plus at least a SGL chain element.
	 */
	CTASSERT(sizeof req->SGL >= sizeof tc + MPS_SGC_SIZE);

	if (cmd->req_len != sizeof *req)
		return (EINVAL);
	if (cmd->rpl_len != sizeof *rpl)
		return (EINVAL);

	mpi_init_sge(cm, req, &req->SGL);
	bzero(&tc, sizeof tc);

	/*
	 * The value of the first two elements is specified in the
	 * Fusion-MPT Message Passing Interface document.
	 */
	tc.ContextSize = 0;
	tc.DetailsLength = 12;
	/*
	 * XXX Is there any reason to fetch a partial image?  I.e. to
	 * set ImageOffset to something other than 0?
	 */
	tc.ImageOffset = 0;
	tc.ImageSize = cmd->len;

	cm->cm_flags |= MPS_CM_FLAGS_DATAIN;

	return (mps_push_sge(cm, &tc, sizeof tc, 0));
}