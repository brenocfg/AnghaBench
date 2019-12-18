#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int dual_ulp_capable; int* is_ulp_fc; scalar_t__* max_qcount; } ;
struct TYPE_10__ {scalar_t__ virt; } ;
struct TYPE_13__ {int /*<<< orphan*/  os; TYPE_3__ config; int /*<<< orphan*/  physical_port; TYPE_1__ bmbx; } ;
typedef  TYPE_4__ sli4_t ;
struct TYPE_11__ {scalar_t__ status; } ;
struct TYPE_14__ {int function_mode; int ulp0_mode; int ulp1_mode; scalar_t__ ulp1_toe_defrq_total; scalar_t__ ulp1_toe_wq_total; scalar_t__ ulp0_toe_defrq_total; scalar_t__ ulp0_toe_wq_total; int /*<<< orphan*/  physical_port; TYPE_2__ hdr; } ;
typedef  TYPE_5__ sli4_res_common_query_fw_config_t ;
typedef  int int32_t ;
struct TYPE_15__ {int /*<<< orphan*/  embed; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int SLI4_FUNCTION_MODE_DUA_MODE ; 
 int SLI4_ULP_MODE_FCOE_INI ; 
 int SLI4_ULP_MODE_FCOE_TGT ; 
 size_t SLI_QTYPE_RQ ; 
 size_t SLI_QTYPE_WQ ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ payload ; 
 int /*<<< orphan*/  sli4_cmd_sli_config_t ; 
 scalar_t__ sli_bmbx_command (TYPE_4__*) ; 
 scalar_t__ sli_cmd_common_query_fw_config (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
sli_query_fw_config(sli4_t *sli4)
{
	/*
	 * Read the device configuration
	 *
	 * Note: Only ulp0 fields contain values
	 */
	if (sli_cmd_common_query_fw_config(sli4, sli4->bmbx.virt, SLI4_BMBX_SIZE)) {
		sli4_res_common_query_fw_config_t   *fw_config =
			(sli4_res_common_query_fw_config_t *)
			(((uint8_t *)sli4->bmbx.virt) + offsetof(sli4_cmd_sli_config_t, payload.embed));

		if (sli_bmbx_command(sli4)) {
			ocs_log_crit(sli4->os, "bootstrap mailbox write fail (QUERY_FW_CONFIG)\n");
			return -1;
		}
		if (fw_config->hdr.status) {
			ocs_log_err(sli4->os, "COMMON_QUERY_FW_CONFIG bad status %#x\n",
				fw_config->hdr.status);
			return -1;
		}

		sli4->physical_port = fw_config->physical_port;
		sli4->config.dual_ulp_capable = ((fw_config->function_mode & SLI4_FUNCTION_MODE_DUA_MODE) == 0 ? 0 : 1);
		sli4->config.is_ulp_fc[0] = ((fw_config->ulp0_mode &
					      (SLI4_ULP_MODE_FCOE_INI |
					       SLI4_ULP_MODE_FCOE_TGT)) == 0 ? 0 : 1);
		sli4->config.is_ulp_fc[1] = ((fw_config->ulp1_mode &
					      (SLI4_ULP_MODE_FCOE_INI |
					       SLI4_ULP_MODE_FCOE_TGT)) == 0 ? 0 : 1);

		if (sli4->config.dual_ulp_capable) {
			/*
			 * Lancer will not support this, so we use the values
			 * from the READ_CONFIG.
			 */
			if (sli4->config.is_ulp_fc[0] &&
			    sli4->config.is_ulp_fc[1]) {
				sli4->config.max_qcount[SLI_QTYPE_WQ] = fw_config->ulp0_toe_wq_total + fw_config->ulp1_toe_wq_total;
				sli4->config.max_qcount[SLI_QTYPE_RQ] = fw_config->ulp0_toe_defrq_total + fw_config->ulp1_toe_defrq_total;
			} else if (sli4->config.is_ulp_fc[0]) {
				sli4->config.max_qcount[SLI_QTYPE_WQ] = fw_config->ulp0_toe_wq_total;
				sli4->config.max_qcount[SLI_QTYPE_RQ] = fw_config->ulp0_toe_defrq_total;
			} else {
				sli4->config.max_qcount[SLI_QTYPE_WQ] = fw_config->ulp1_toe_wq_total;
				sli4->config.max_qcount[SLI_QTYPE_RQ] = fw_config->ulp1_toe_defrq_total;
			}
		}
	} else {
		ocs_log_err(sli4->os, "bad QUERY_FW_CONFIG write\n");
		return -1;
	}
	return 0;
}