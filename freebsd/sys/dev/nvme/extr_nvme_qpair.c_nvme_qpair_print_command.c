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
struct nvme_qpair {scalar_t__ id; int /*<<< orphan*/  ctrlr; } ;
struct nvme_command {int /*<<< orphan*/  cdw15; int /*<<< orphan*/  cdw14; int /*<<< orphan*/  cdw13; int /*<<< orphan*/  cdw12; int /*<<< orphan*/  cdw11; int /*<<< orphan*/  cdw10; scalar_t__ prp2; scalar_t__ prp1; scalar_t__ mptr; int /*<<< orphan*/  rsvd3; int /*<<< orphan*/  rsvd2; int /*<<< orphan*/  nsid; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_admin_qpair_print_command (struct nvme_qpair*,struct nvme_command*) ; 
 int /*<<< orphan*/  nvme_io_qpair_print_command (struct nvme_qpair*,struct nvme_command*) ; 
 int /*<<< orphan*/  nvme_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvme_verbose_cmd_dump ; 

__attribute__((used)) static void
nvme_qpair_print_command(struct nvme_qpair *qpair, struct nvme_command *cmd)
{
	if (qpair->id == 0)
		nvme_admin_qpair_print_command(qpair, cmd);
	else
		nvme_io_qpair_print_command(qpair, cmd);
	if (nvme_verbose_cmd_dump) {
		nvme_printf(qpair->ctrlr,
		    "nsid:%#x rsvd2:%#x rsvd3:%#x mptr:%#jx prp1:%#jx prp2:%#jx\n",
		    cmd->nsid, cmd->rsvd2, cmd->rsvd3, (uintmax_t)cmd->mptr,
		    (uintmax_t)cmd->prp1, (uintmax_t)cmd->prp2);
		nvme_printf(qpair->ctrlr,
		    "cdw10: %#x cdw11:%#x cdw12:%#x cdw13:%#x cdw14:%#x cdw15:%#x\n",
		    cmd->cdw10, cmd->cdw11, cmd->cdw12, cmd->cdw13, cmd->cdw14,
		    cmd->cdw15);
	}
}