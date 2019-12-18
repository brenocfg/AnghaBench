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
typedef  int /*<<< orphan*/  uintmax_t ;
struct nvme_command {int opc; int fuse; int cid; int rsvd2; int rsvd3; int /*<<< orphan*/  nsid; int /*<<< orphan*/  cdw15; int /*<<< orphan*/  cdw14; int /*<<< orphan*/  cdw13; int /*<<< orphan*/  cdw12; int /*<<< orphan*/  cdw11; int /*<<< orphan*/  cdw10; int /*<<< orphan*/  prp2; int /*<<< orphan*/  prp1; int /*<<< orphan*/  mptr; } ;

/* Variables and functions */
 int le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 

void
nvme_dump_command(struct nvme_command *cmd)
{

	printf(
"opc:%x f:%x cid:%x nsid:%x r2:%x r3:%x mptr:%jx prp1:%jx prp2:%jx cdw:%x %x %x %x %x %x\n",
	    cmd->opc, cmd->fuse, cmd->cid, le32toh(cmd->nsid),
	    cmd->rsvd2, cmd->rsvd3,
	    (uintmax_t)le64toh(cmd->mptr), (uintmax_t)le64toh(cmd->prp1), (uintmax_t)le64toh(cmd->prp2),
	    le32toh(cmd->cdw10), le32toh(cmd->cdw11), le32toh(cmd->cdw12),
	    le32toh(cmd->cdw13), le32toh(cmd->cdw14), le32toh(cmd->cdw15));
}