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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct nvme_command {int cdw10; void* nsid; int /*<<< orphan*/  opc; } ;
struct nvme_request {struct nvme_command cmd; } ;
struct nvme_controller {int dummy; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_OPC_GET_LOG_PAGE ; 
 void* htole32 (int) ; 
 struct nvme_request* nvme_allocate_request_vaddr (void*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_admin_request (struct nvme_controller*,struct nvme_request*) ; 

void
nvme_ctrlr_cmd_get_log_page(struct nvme_controller *ctrlr, uint8_t log_page,
    uint32_t nsid, void *payload, uint32_t payload_size, nvme_cb_fn_t cb_fn,
    void *cb_arg)
{
	struct nvme_request *req;
	struct nvme_command *cmd;

	req = nvme_allocate_request_vaddr(payload, payload_size, cb_fn, cb_arg);

	cmd = &req->cmd;
	cmd->opc = NVME_OPC_GET_LOG_PAGE;
	cmd->nsid = htole32(nsid);
	cmd->cdw10 = ((payload_size/sizeof(uint32_t)) - 1) << 16;
	cmd->cdw10 |= log_page;
	cmd->cdw10 = htole32(cmd->cdw10);

	nvme_ctrlr_submit_admin_request(ctrlr, req);
}