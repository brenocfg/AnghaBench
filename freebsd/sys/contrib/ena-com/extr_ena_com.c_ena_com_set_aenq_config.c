#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ena_com_admin_queue {int dummy; } ;
struct ena_com_dev {struct ena_com_admin_queue admin_queue; } ;
struct ena_admin_set_feat_resp {int dummy; } ;
struct TYPE_11__ {int enabled_groups; } ;
struct TYPE_12__ {TYPE_5__ aenq; } ;
struct TYPE_10__ {int /*<<< orphan*/  feature_id; } ;
struct TYPE_9__ {scalar_t__ flags; int /*<<< orphan*/  opcode; } ;
struct ena_admin_set_feat_cmd {TYPE_6__ u; TYPE_4__ feat_common; TYPE_3__ aq_common_descriptor; } ;
struct TYPE_7__ {int supported_groups; } ;
struct TYPE_8__ {TYPE_1__ aenq; } ;
struct ena_admin_get_feat_resp {TYPE_2__ u; } ;
struct ena_admin_aq_entry {int dummy; } ;
struct ena_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_AENQ_CONFIG ; 
 int /*<<< orphan*/  ENA_ADMIN_SET_FEATURE ; 
 int ENA_COM_UNSUPPORTED ; 
 int ena_com_execute_admin_command (struct ena_com_admin_queue*,struct ena_admin_aq_entry*,int,struct ena_admin_acq_entry*,int) ; 
 int ena_com_get_feature (struct ena_com_dev*,struct ena_admin_get_feat_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_err (char*,int) ; 
 int /*<<< orphan*/  ena_trc_info (char*) ; 
 int /*<<< orphan*/  ena_trc_warn (char*,int,int) ; 
 int /*<<< orphan*/  memset (struct ena_admin_set_feat_cmd*,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_set_aenq_config(struct ena_com_dev *ena_dev, u32 groups_flag)
{
	struct ena_com_admin_queue *admin_queue;
	struct ena_admin_set_feat_cmd cmd;
	struct ena_admin_set_feat_resp resp;
	struct ena_admin_get_feat_resp get_resp;
	int ret;

	ret = ena_com_get_feature(ena_dev, &get_resp, ENA_ADMIN_AENQ_CONFIG, 0);
	if (ret) {
		ena_trc_info("Can't get aenq configuration\n");
		return ret;
	}

	if ((get_resp.u.aenq.supported_groups & groups_flag) != groups_flag) {
		ena_trc_warn("Trying to set unsupported aenq events. supported flag: 0x%x asked flag: 0x%x\n",
			     get_resp.u.aenq.supported_groups,
			     groups_flag);
		return ENA_COM_UNSUPPORTED;
	}

	memset(&cmd, 0x0, sizeof(cmd));
	admin_queue = &ena_dev->admin_queue;

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags = 0;
	cmd.feat_common.feature_id = ENA_ADMIN_AENQ_CONFIG;
	cmd.u.aenq.enabled_groups = groups_flag;

	ret = ena_com_execute_admin_command(admin_queue,
					    (struct ena_admin_aq_entry *)&cmd,
					    sizeof(cmd),
					    (struct ena_admin_acq_entry *)&resp,
					    sizeof(resp));

	if (unlikely(ret))
		ena_trc_err("Failed to config AENQ ret: %d\n", ret);

	return ret;
}