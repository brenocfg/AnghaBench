#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
typedef  int /*<<< orphan*/  ocs_hw_port_control_cb_t ;
typedef  int /*<<< orphan*/  ocs_hw_linkcfg_e ;
struct TYPE_14__ {scalar_t__ virt; } ;
struct TYPE_13__ {TYPE_6__ dma_resp; TYPE_6__ dma_cmd; int /*<<< orphan*/  opts; void* arg; int /*<<< orphan*/  cb; } ;
typedef  TYPE_2__ ocs_hw_linkcfg_cb_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_POLL ; 
 int OCS_HW_DMTF_CLP_CMD_MAX ; 
 scalar_t__ OCS_HW_DMTF_CLP_RSP_MAX ; 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 scalar_t__ ocs_dma_alloc (int /*<<< orphan*/ ,TYPE_6__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 char* ocs_hw_clp_from_linkcfg (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_hw_exec_dmtf_clp_cmd (TYPE_1__*,TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_hw_linkcfg_dmtf_clp_cb ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_2__* ocs_malloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memcpy (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocs_snprintf (char*,int,char*,char const*) ; 
 scalar_t__ ocs_strlen (char*) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_set_linkcfg_lancer(ocs_hw_t *hw, ocs_hw_linkcfg_e value, uint32_t opts, ocs_hw_port_control_cb_t cb, void *arg)
{
	char cmd[OCS_HW_DMTF_CLP_CMD_MAX];
	ocs_hw_linkcfg_cb_arg_t *cb_arg;
	const char *value_str = NULL;
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;

	/* translate ocs_hw_linkcfg_e to CLP string */
	value_str = ocs_hw_clp_from_linkcfg(value);

	/* allocate memory for callback argument */
	cb_arg = ocs_malloc(hw->os, sizeof(*cb_arg), OCS_M_NOWAIT);
	if (cb_arg == NULL) {
		ocs_log_err(hw->os, "failed to malloc cb_arg");
		return OCS_HW_RTN_NO_MEMORY;
	}

	ocs_snprintf(cmd, OCS_HW_DMTF_CLP_CMD_MAX, "set / OEMELX_LinkConfig=%s", value_str);
	/* allocate DMA for command  */
	if (ocs_dma_alloc(hw->os, &cb_arg->dma_cmd, ocs_strlen(cmd)+1, 4096)) {
		ocs_log_err(hw->os, "malloc failed\n");
		ocs_free(hw->os, cb_arg, sizeof(*cb_arg));
		return OCS_HW_RTN_NO_MEMORY;
	}
	ocs_memset(cb_arg->dma_cmd.virt, 0, ocs_strlen(cmd)+1);
	ocs_memcpy(cb_arg->dma_cmd.virt, cmd, ocs_strlen(cmd));

	/* allocate DMA for response */
	if (ocs_dma_alloc(hw->os, &cb_arg->dma_resp, OCS_HW_DMTF_CLP_RSP_MAX, 4096)) {
		ocs_log_err(hw->os, "malloc failed\n");
		ocs_dma_free(hw->os, &cb_arg->dma_cmd);
		ocs_free(hw->os, cb_arg, sizeof(*cb_arg));
		return OCS_HW_RTN_NO_MEMORY;
	}
	cb_arg->cb = cb;
	cb_arg->arg = arg;
	cb_arg->opts = opts;

	rc = ocs_hw_exec_dmtf_clp_cmd(hw, &cb_arg->dma_cmd, &cb_arg->dma_resp,
					opts, ocs_hw_linkcfg_dmtf_clp_cb, cb_arg);

	if (opts == OCS_CMD_POLL || rc != OCS_HW_RTN_SUCCESS) {
		/* if failed, or polling, free memory here; if success and not
		 * polling, will free in callback function
		 */
		if (rc) {
			ocs_log_test(hw->os, "CLP cmd=\"%s\" failed\n",
					(char *)cb_arg->dma_cmd.virt);
		}
		ocs_dma_free(hw->os, &cb_arg->dma_cmd);
		ocs_dma_free(hw->os, &cb_arg->dma_resp);
		ocs_free(hw->os, cb_arg, sizeof(*cb_arg));
	}
	return rc;
}