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
struct nvme_command {int /*<<< orphan*/  prp1; void* cdw11; void* cdw10; int /*<<< orphan*/  opc; } ;
struct nvme_request {struct nvme_command cmd; } ;
struct nvme_qpair {int num_entries; int id; int vector; int /*<<< orphan*/  cpl_bus_addr; } ;
struct nvme_controller {int dummy; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_OPC_CREATE_IO_CQ ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 struct nvme_request* nvme_allocate_request_null (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_admin_request (struct nvme_controller*,struct nvme_request*) ; 

void
nvme_ctrlr_cmd_create_io_cq(struct nvme_controller *ctrlr,
    struct nvme_qpair *io_que, nvme_cb_fn_t cb_fn, void *cb_arg)
{
	struct nvme_request *req;
	struct nvme_command *cmd;

	req = nvme_allocate_request_null(cb_fn, cb_arg);

	cmd = &req->cmd;
	cmd->opc = NVME_OPC_CREATE_IO_CQ;

	/*
	 * TODO: create a create io completion queue command data
	 *  structure.
	 */
	cmd->cdw10 = htole32(((io_que->num_entries-1) << 16) | io_que->id);
	/* 0x3 = interrupts enabled | physically contiguous */
	cmd->cdw11 = htole32((io_que->vector << 16) | 0x3);
	cmd->prp1 = htole64(io_que->cpl_bus_addr);

	nvme_ctrlr_submit_admin_request(ctrlr, req);
}