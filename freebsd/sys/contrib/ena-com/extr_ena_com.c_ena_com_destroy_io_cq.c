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
struct ena_com_io_cq {int /*<<< orphan*/  idx; } ;
struct ena_com_admin_queue {int dummy; } ;
struct ena_com_dev {struct ena_com_admin_queue admin_queue; } ;
struct ena_admin_aq_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct ena_admin_aq_destroy_cq_cmd {TYPE_1__ aq_common_descriptor; int /*<<< orphan*/  cq_idx; } ;
struct ena_admin_acq_entry {int dummy; } ;
struct ena_admin_acq_destroy_cq_resp_desc {int dummy; } ;
typedef  int /*<<< orphan*/  destroy_resp ;
typedef  int /*<<< orphan*/  destroy_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_DESTROY_CQ ; 
 int ENA_COM_NO_DEVICE ; 
 int ena_com_execute_admin_command (struct ena_com_admin_queue*,struct ena_admin_aq_entry*,int,struct ena_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  ena_trc_err (char*,int) ; 
 int /*<<< orphan*/  memset (struct ena_admin_aq_destroy_cq_cmd*,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_destroy_io_cq(struct ena_com_dev *ena_dev,
			  struct ena_com_io_cq *io_cq)
{
	struct ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	struct ena_admin_aq_destroy_cq_cmd destroy_cmd;
	struct ena_admin_acq_destroy_cq_resp_desc destroy_resp;
	int ret;

	memset(&destroy_cmd, 0x0, sizeof(destroy_cmd));

	destroy_cmd.cq_idx = io_cq->idx;
	destroy_cmd.aq_common_descriptor.opcode = ENA_ADMIN_DESTROY_CQ;

	ret = ena_com_execute_admin_command(admin_queue,
					    (struct ena_admin_aq_entry *)&destroy_cmd,
					    sizeof(destroy_cmd),
					    (struct ena_admin_acq_entry *)&destroy_resp,
					    sizeof(destroy_resp));

	if (unlikely(ret && (ret != ENA_COM_NO_DEVICE)))
		ena_trc_err("Failed to destroy IO CQ. error: %d\n", ret);

	return ret;
}