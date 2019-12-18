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
struct mpr_usr_command {int req_len; int rpl_len; scalar_t__ len; } ;
struct mpr_command {int /*<<< orphan*/  cm_flags; scalar_t__ cm_req; } ;
struct TYPE_3__ {scalar_t__ ImageSize; int /*<<< orphan*/  SGL; scalar_t__ ImageOffset; } ;
typedef  int /*<<< orphan*/  MPI2_FW_UPLOAD_REPLY ;
typedef  TYPE_1__ MPI25_FW_UPLOAD_REQUEST ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MPR_CM_FLAGS_DATAIN ; 
 int /*<<< orphan*/  mpr_init_sge (struct mpr_command*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mpr_push_ieee_sge (struct mpr_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpi_pre_fw_upload(struct mpr_command *cm, struct mpr_usr_command *cmd)
{
	MPI25_FW_UPLOAD_REQUEST *req = (void *)cm->cm_req;
	MPI2_FW_UPLOAD_REPLY *rpl;

	if (cmd->req_len != sizeof *req)
		return (EINVAL);
	if (cmd->rpl_len != sizeof *rpl)
		return (EINVAL);

	mpr_init_sge(cm, req, &req->SGL);
	if (cmd->len == 0) {
		/* Perhaps just asking what the size of the fw is? */
		return (0);
	}

	req->ImageOffset = 0;
	req->ImageSize = cmd->len;

	cm->cm_flags |= MPR_CM_FLAGS_DATAIN;

	return (mpr_push_ieee_sge(cm, &req->SGL, 0));
}