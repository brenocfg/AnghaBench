#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ena_host_attribute {int /*<<< orphan*/  debug_area_size; int /*<<< orphan*/  host_info_dma_addr; int /*<<< orphan*/  debug_area_dma_addr; } ;
struct ena_com_admin_queue {int dummy; } ;
struct ena_com_dev {struct ena_com_admin_queue admin_queue; struct ena_host_attribute host_attr; } ;
struct ena_admin_set_feat_resp {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  debug_area_size; int /*<<< orphan*/  os_info_ba; int /*<<< orphan*/  debug_ba; } ;
struct TYPE_8__ {TYPE_3__ host_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  feature_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  opcode; } ;
struct ena_admin_set_feat_cmd {TYPE_4__ u; TYPE_2__ feat_common; TYPE_1__ aq_common_descriptor; } ;
struct ena_admin_aq_entry {int dummy; } ;
struct ena_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_HOST_ATTR_CONFIG ; 
 int /*<<< orphan*/  ENA_ADMIN_SET_FEATURE ; 
 int ena_com_execute_admin_command (struct ena_com_admin_queue*,struct ena_admin_aq_entry*,int,struct ena_admin_acq_entry*,int) ; 
 int ena_com_mem_addr_set (struct ena_com_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_err (char*,...) ; 
 int /*<<< orphan*/  memset (struct ena_admin_set_feat_cmd*,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_set_host_attributes(struct ena_com_dev *ena_dev)
{
	struct ena_host_attribute *host_attr = &ena_dev->host_attr;
	struct ena_com_admin_queue *admin_queue;
	struct ena_admin_set_feat_cmd cmd;
	struct ena_admin_set_feat_resp resp;

	int ret;

	/* Host attribute config is called before ena_com_get_dev_attr_feat
	 * so ena_com can't check if the feature is supported.
	 */

	memset(&cmd, 0x0, sizeof(cmd));
	admin_queue = &ena_dev->admin_queue;

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.feat_common.feature_id = ENA_ADMIN_HOST_ATTR_CONFIG;

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.u.host_attr.debug_ba,
				   host_attr->debug_area_dma_addr);
	if (unlikely(ret)) {
		ena_trc_err("memory address set failed\n");
		return ret;
	}

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.u.host_attr.os_info_ba,
				   host_attr->host_info_dma_addr);
	if (unlikely(ret)) {
		ena_trc_err("memory address set failed\n");
		return ret;
	}

	cmd.u.host_attr.debug_area_size = host_attr->debug_area_size;

	ret = ena_com_execute_admin_command(admin_queue,
					    (struct ena_admin_aq_entry *)&cmd,
					    sizeof(cmd),
					    (struct ena_admin_acq_entry *)&resp,
					    sizeof(resp));

	if (unlikely(ret))
		ena_trc_err("Failed to set host attributes: %d\n", ret);

	return ret;
}