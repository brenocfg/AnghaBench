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
struct nvme_command {int opc; int /*<<< orphan*/  nsid; int /*<<< orphan*/  cid; int /*<<< orphan*/  cdw12; int /*<<< orphan*/  cdw10; int /*<<< orphan*/  cdw11; } ;

/* Variables and functions */
#define  NVME_OPC_COMPARE 139 
#define  NVME_OPC_DATASET_MANAGEMENT 138 
#define  NVME_OPC_FLUSH 137 
#define  NVME_OPC_READ 136 
#define  NVME_OPC_RESERVATION_ACQUIRE 135 
#define  NVME_OPC_RESERVATION_REGISTER 134 
#define  NVME_OPC_RESERVATION_RELEASE 133 
#define  NVME_OPC_RESERVATION_REPORT 132 
#define  NVME_OPC_VERIFY 131 
#define  NVME_OPC_WRITE 130 
#define  NVME_OPC_WRITE_UNCORRECTABLE 129 
#define  NVME_OPC_WRITE_ZEROES 128 
 int /*<<< orphan*/  get_io_opcode_string (int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void
nvme_io_qpair_print_command(struct nvme_qpair *qpair,
    struct nvme_command *cmd)
{

	switch (cmd->opc) {
	case NVME_OPC_WRITE:
	case NVME_OPC_READ:
	case NVME_OPC_WRITE_UNCORRECTABLE:
	case NVME_OPC_COMPARE:
	case NVME_OPC_WRITE_ZEROES:
	case NVME_OPC_VERIFY:
		nvme_printf(qpair->ctrlr, "%s sqid:%d cid:%d nsid:%d "
		    "lba:%llu len:%d\n",
		    get_io_opcode_string(cmd->opc), qpair->id, cmd->cid, le32toh(cmd->nsid),
		    ((unsigned long long)le32toh(cmd->cdw11) << 32) + le32toh(cmd->cdw10),
		    (le32toh(cmd->cdw12) & 0xFFFF) + 1);
		break;
	case NVME_OPC_FLUSH:
	case NVME_OPC_DATASET_MANAGEMENT:
	case NVME_OPC_RESERVATION_REGISTER:
	case NVME_OPC_RESERVATION_REPORT:
	case NVME_OPC_RESERVATION_ACQUIRE:
	case NVME_OPC_RESERVATION_RELEASE:
		nvme_printf(qpair->ctrlr, "%s sqid:%d cid:%d nsid:%d\n",
		    get_io_opcode_string(cmd->opc), qpair->id, cmd->cid, le32toh(cmd->nsid));
		break;
	default:
		nvme_printf(qpair->ctrlr, "%s (%02x) sqid:%d cid:%d nsid:%d\n",
		    get_io_opcode_string(cmd->opc), cmd->opc, qpair->id,
		    cmd->cid, le32toh(cmd->nsid));
		break;
	}
}