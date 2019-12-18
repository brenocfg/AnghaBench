#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mpr_usr_command {int req_len; int rpl_len; } ;
struct mpr_command {scalar_t__ cm_sglsize; int /*<<< orphan*/ * cm_sge; scalar_t__ cm_req; } ;
typedef  int /*<<< orphan*/  MPI2_IOC_FACTS_REQUEST ;
typedef  int /*<<< orphan*/  MPI2_IOC_FACTS_REPLY ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
mpi_pre_ioc_facts(struct mpr_command *cm, struct mpr_usr_command *cmd)
{
	MPI2_IOC_FACTS_REQUEST *req = (void *)cm->cm_req;
	MPI2_IOC_FACTS_REPLY *rpl;

	if (cmd->req_len != sizeof *req)
		return (EINVAL);
	if (cmd->rpl_len != sizeof *rpl)
		return (EINVAL);

	cm->cm_sge = NULL;
	cm->cm_sglsize = 0;
	return (0);
}