#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_5__ {int personality; int offload_tc; } ;
struct ecore_hwfn {TYPE_3__* p_dev; TYPE_2__ hw_info; } ;
struct ecore_dcbx_results {TYPE_1__* arr; } ;
typedef  enum ecore_pci_personality { ____Placeholder_ecore_pci_personality } ecore_pci_personality ;
typedef  enum dcbx_protocol_type { ____Placeholder_dcbx_protocol_type } dcbx_protocol_type ;
struct TYPE_6__ {int /*<<< orphan*/  mf_bits; } ;
struct TYPE_4__ {int enable; int priority; int tc; scalar_t__ dscp_val; int dscp_enable; int dont_add_vlan0; int /*<<< orphan*/  update; } ;

/* Variables and functions */
 int DCBX_PROTOCOL_ROCE ; 
 int /*<<< orphan*/  DORQ_REG_PF_PCP_BB_K2 ; 
 int /*<<< orphan*/  DORQ_REG_TAG1_OVRD_MODE ; 
 scalar_t__ ECORE_DCBX_DSCP_DISABLED ; 
 int /*<<< orphan*/  ECORE_MF_UFP_SPECIFIC ; 
 scalar_t__ OSAL_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_DCB_DSCP ; 
 scalar_t__ ecore_dcbx_get_dscp_value (struct ecore_hwfn*,int) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ecore_dcbx_set_params(struct ecore_dcbx_results *p_data,
		      struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
		      bool enable, u8 prio, u8 tc,
		      enum dcbx_protocol_type type,
		      enum ecore_pci_personality personality)
{
	/* PF update ramrod data */
	p_data->arr[type].enable = enable;
	p_data->arr[type].priority = prio;
	p_data->arr[type].tc = tc;
	p_data->arr[type].dscp_val = ecore_dcbx_get_dscp_value(p_hwfn, prio);
	if (p_data->arr[type].dscp_val == ECORE_DCBX_DSCP_DISABLED) {
		p_data->arr[type].dscp_enable = false;
		p_data->arr[type].dscp_val = 0;
	} else
		p_data->arr[type].dscp_enable = enable;

	p_data->arr[type].update = UPDATE_DCB_DSCP;

	/* Do not add valn tag 0 when DCB is enabled and port is in UFP mode */
	if (OSAL_TEST_BIT(ECORE_MF_UFP_SPECIFIC, &p_hwfn->p_dev->mf_bits))
		p_data->arr[type].dont_add_vlan0 = true;

	/* QM reconf data */
	if (p_hwfn->hw_info.personality == personality)
		p_hwfn->hw_info.offload_tc = tc;

	/* Configure dcbx vlan priority in doorbell block for roce EDPM */
	if (OSAL_TEST_BIT(ECORE_MF_UFP_SPECIFIC, &p_hwfn->p_dev->mf_bits) &&
	    (type == DCBX_PROTOCOL_ROCE)) {
		ecore_wr(p_hwfn, p_ptt, DORQ_REG_TAG1_OVRD_MODE, 1);
		ecore_wr(p_hwfn, p_ptt, DORQ_REG_PF_PCP_BB_K2, prio << 1);
	}
}