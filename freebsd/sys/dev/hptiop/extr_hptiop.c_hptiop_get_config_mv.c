#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; int /*<<< orphan*/  context; int /*<<< orphan*/  result; int /*<<< orphan*/  type; scalar_t__ flags; } ;
struct hpt_iop_request_get_config {TYPE_1__ header; } ;
struct hpt_iop_hba {struct hpt_iop_request_get_config* ctlcfg_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP_REQUEST_TYPE_GET_CONFIG ; 
 int /*<<< orphan*/  IOP_RESULT_PENDING ; 
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  MVIOP_CMD_TYPE_GET_CONFIG ; 
 scalar_t__ hptiop_send_sync_request_mv (struct hpt_iop_hba*,struct hpt_iop_request_get_config*,int) ; 

__attribute__((used)) static int hptiop_get_config_mv(struct hpt_iop_hba * hba,
				struct hpt_iop_request_get_config * config)
{
	struct hpt_iop_request_get_config *req;

	if (!(req = hba->ctlcfg_ptr))
		return -1;

	req->header.flags = 0;
	req->header.type = IOP_REQUEST_TYPE_GET_CONFIG;
	req->header.size = sizeof(struct hpt_iop_request_get_config);
	req->header.result = IOP_RESULT_PENDING;
	req->header.context = MVIOP_CMD_TYPE_GET_CONFIG;

	if (hptiop_send_sync_request_mv(hba, req, 20000)) {
		KdPrint(("hptiop: get config send cmd failed"));
		return -1;
	}

	*config = *req;
	return 0;
}