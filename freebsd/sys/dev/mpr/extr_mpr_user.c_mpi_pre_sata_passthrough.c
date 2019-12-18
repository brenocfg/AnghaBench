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
struct mpr_usr_command {int req_len; int rpl_len; } ;
struct mpr_command {scalar_t__ cm_req; } ;
struct TYPE_3__ {int /*<<< orphan*/  SGL; } ;
typedef  TYPE_1__ MPI2_SATA_PASSTHROUGH_REQUEST ;
typedef  int /*<<< orphan*/  MPI2_SATA_PASSTHROUGH_REPLY ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mpr_init_sge (struct mpr_command*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mpi_pre_sata_passthrough(struct mpr_command *cm, struct mpr_usr_command *cmd)
{
	MPI2_SATA_PASSTHROUGH_REQUEST *req = (void *)cm->cm_req;
	MPI2_SATA_PASSTHROUGH_REPLY *rpl;

	if (cmd->req_len != sizeof *req)
		return (EINVAL);
	if (cmd->rpl_len != sizeof *rpl)
		return (EINVAL);

	mpr_init_sge(cm, req, &req->SGL);
	return (0);
}