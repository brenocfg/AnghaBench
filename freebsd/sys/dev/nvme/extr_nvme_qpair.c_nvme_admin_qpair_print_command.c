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
struct nvme_qpair {int /*<<< orphan*/  id; int /*<<< orphan*/  ctrlr; } ;
struct nvme_command {int /*<<< orphan*/  cdw11; int /*<<< orphan*/  cdw10; int /*<<< orphan*/  nsid; int /*<<< orphan*/  cid; int /*<<< orphan*/  opc; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_admin_opcode_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_admin_qpair_print_command(struct nvme_qpair *qpair,
    struct nvme_command *cmd)
{

	nvme_printf(qpair->ctrlr, "%s (%02x) sqid:%d cid:%d nsid:%x "
	    "cdw10:%08x cdw11:%08x\n",
	    get_admin_opcode_string(cmd->opc), cmd->opc, qpair->id, cmd->cid,
	    le32toh(cmd->nsid), le32toh(cmd->cdw10), le32toh(cmd->cdw11));
}