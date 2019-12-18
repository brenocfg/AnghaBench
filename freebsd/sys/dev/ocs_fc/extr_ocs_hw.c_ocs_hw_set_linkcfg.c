#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
typedef  int /*<<< orphan*/  ocs_hw_port_control_cb_t ;
typedef  int /*<<< orphan*/  ocs_hw_linkcfg_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_PF ; 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_VF ; 
 scalar_t__ SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int /*<<< orphan*/  ocs_hw_set_linkcfg_lancer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ocs_hw_set_linkcfg_skyhawk (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sli_get_if_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_link_is_configurable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_set_linkcfg(ocs_hw_t *hw, ocs_hw_linkcfg_e value, uint32_t opts, ocs_hw_port_control_cb_t cb, void *arg)
{
	if (!sli_link_is_configurable(&hw->sli)) {
		ocs_log_debug(hw->os, "Function not supported\n");
		return OCS_HW_RTN_ERROR;
	}

	if (SLI4_IF_TYPE_LANCER_FC_ETH == sli_get_if_type(&hw->sli)) {
		return ocs_hw_set_linkcfg_lancer(hw, value, opts, cb, arg);
	} else if ((SLI4_IF_TYPE_BE3_SKH_PF == sli_get_if_type(&hw->sli)) ||
		   (SLI4_IF_TYPE_BE3_SKH_VF == sli_get_if_type(&hw->sli))) {
		return ocs_hw_set_linkcfg_skyhawk(hw, value, opts, cb, arg);
	} else {
		ocs_log_test(hw->os, "Function not supported for this IF_TYPE\n");
		return OCS_HW_RTN_ERROR;
	}
}