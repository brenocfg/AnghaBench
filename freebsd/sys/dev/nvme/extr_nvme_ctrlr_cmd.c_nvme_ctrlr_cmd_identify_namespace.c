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
typedef  int /*<<< orphan*/  uint32_t ;
struct nvme_command {int /*<<< orphan*/  nsid; int /*<<< orphan*/  opc; } ;
struct nvme_request {struct nvme_command cmd; } ;
struct nvme_namespace_data {int dummy; } ;
struct nvme_controller {int dummy; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_OPC_IDENTIFY ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 struct nvme_request* nvme_allocate_request_vaddr (void*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_admin_request (struct nvme_controller*,struct nvme_request*) ; 

void
nvme_ctrlr_cmd_identify_namespace(struct nvme_controller *ctrlr, uint32_t nsid,
	void *payload, nvme_cb_fn_t cb_fn, void *cb_arg)
{
	struct nvme_request *req;
	struct nvme_command *cmd;

	req = nvme_allocate_request_vaddr(payload,
	    sizeof(struct nvme_namespace_data), cb_fn, cb_arg);

	cmd = &req->cmd;
	cmd->opc = NVME_OPC_IDENTIFY;

	/*
	 * TODO: create an identify command data structure
	 */
	cmd->nsid = htole32(nsid);

	nvme_ctrlr_submit_admin_request(ctrlr, req);
}