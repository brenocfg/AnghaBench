#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ena_rss {int /*<<< orphan*/  hash_ctrl_dma_addr; struct ena_admin_feature_rss_hash_control* hash_ctrl; } ;
struct ena_com_admin_queue {int dummy; } ;
struct ena_com_dev {struct ena_rss rss; struct ena_com_admin_queue admin_queue; } ;
struct ena_admin_set_feat_resp {int dummy; } ;
struct TYPE_10__ {int length; int /*<<< orphan*/  address; } ;
struct TYPE_8__ {int enabled_input_sort; } ;
struct TYPE_9__ {TYPE_3__ flow_hash_input; } ;
struct TYPE_7__ {int /*<<< orphan*/  feature_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct ena_admin_set_feat_cmd {TYPE_5__ control_buffer; TYPE_4__ u; TYPE_2__ feat_common; TYPE_1__ aq_common_descriptor; } ;
struct ena_admin_feature_rss_hash_control {int dummy; } ;
struct ena_admin_aq_entry {int dummy; } ;
struct ena_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK ; 
 int ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L3_SORT_MASK ; 
 int ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L4_SORT_MASK ; 
 int /*<<< orphan*/  ENA_ADMIN_RSS_HASH_INPUT ; 
 int /*<<< orphan*/  ENA_ADMIN_SET_FEATURE ; 
 int ENA_COM_UNSUPPORTED ; 
 int /*<<< orphan*/  ena_com_check_supported_feature_id (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int ena_com_execute_admin_command (struct ena_com_admin_queue*,struct ena_admin_aq_entry*,int,struct ena_admin_acq_entry*,int) ; 
 int ena_com_mem_addr_set (struct ena_com_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_err (char*,...) ; 
 int /*<<< orphan*/  memset (struct ena_admin_set_feat_cmd*,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_set_hash_ctrl(struct ena_com_dev *ena_dev)
{
	struct ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	struct ena_rss *rss = &ena_dev->rss;
	struct ena_admin_feature_rss_hash_control *hash_ctrl = rss->hash_ctrl;
	struct ena_admin_set_feat_cmd cmd;
	struct ena_admin_set_feat_resp resp;
	int ret;

	if (!ena_com_check_supported_feature_id(ena_dev,
						ENA_ADMIN_RSS_HASH_INPUT)) {
		ena_trc_dbg("Feature %d isn't supported\n",
			    ENA_ADMIN_RSS_HASH_INPUT);
		return ENA_COM_UNSUPPORTED;
	}

	memset(&cmd, 0x0, sizeof(cmd));

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags =
		ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK;
	cmd.feat_common.feature_id = ENA_ADMIN_RSS_HASH_INPUT;
	cmd.u.flow_hash_input.enabled_input_sort =
		ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L3_SORT_MASK |
		ENA_ADMIN_FEATURE_RSS_FLOW_HASH_INPUT_L4_SORT_MASK;

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.control_buffer.address,
				   rss->hash_ctrl_dma_addr);
	if (unlikely(ret)) {
		ena_trc_err("memory address set failed\n");
		return ret;
	}
	cmd.control_buffer.length = sizeof(*hash_ctrl);

	ret = ena_com_execute_admin_command(admin_queue,
					    (struct ena_admin_aq_entry *)&cmd,
					    sizeof(cmd),
					    (struct ena_admin_acq_entry *)&resp,
					    sizeof(resp));
	if (unlikely(ret))
		ena_trc_err("Failed to set hash input. error: %d\n", ret);

	return ret;
}