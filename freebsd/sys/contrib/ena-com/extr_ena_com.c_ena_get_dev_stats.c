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
struct ena_admin_acq_get_stats_resp {int dummy; } ;
struct TYPE_2__ {scalar_t__ flags; int /*<<< orphan*/  opcode; } ;
struct ena_admin_aq_get_stats_cmd {int type; TYPE_1__ aq_common_descriptor; } ;
struct ena_com_stats_ctx {struct ena_admin_acq_get_stats_resp get_resp; struct ena_admin_aq_get_stats_cmd get_cmd; } ;
struct ena_com_admin_queue {int dummy; } ;
struct ena_com_dev {struct ena_com_admin_queue admin_queue; } ;
struct ena_admin_aq_entry {int dummy; } ;
struct ena_admin_acq_entry {int dummy; } ;
typedef  enum ena_admin_get_stats_type { ____Placeholder_ena_admin_get_stats_type } ena_admin_get_stats_type ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_GET_STATS ; 
 int ena_com_execute_admin_command (struct ena_com_admin_queue*,struct ena_admin_aq_entry*,int,struct ena_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  ena_trc_err (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_get_dev_stats(struct ena_com_dev *ena_dev,
			     struct ena_com_stats_ctx *ctx,
			     enum ena_admin_get_stats_type type)
{
	struct ena_admin_aq_get_stats_cmd *get_cmd = &ctx->get_cmd;
	struct ena_admin_acq_get_stats_resp *get_resp = &ctx->get_resp;
	struct ena_com_admin_queue *admin_queue;
	int ret;

	admin_queue = &ena_dev->admin_queue;

	get_cmd->aq_common_descriptor.opcode = ENA_ADMIN_GET_STATS;
	get_cmd->aq_common_descriptor.flags = 0;
	get_cmd->type = type;

	ret =  ena_com_execute_admin_command(admin_queue,
					     (struct ena_admin_aq_entry *)get_cmd,
					     sizeof(*get_cmd),
					     (struct ena_admin_acq_entry *)get_resp,
					     sizeof(*get_resp));

	if (unlikely(ret))
		ena_trc_err("Failed to get stats. error: %d\n", ret);

	return ret;
}