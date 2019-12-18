#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dcbx_params {scalar_t__* ets_pri_tc_tbl; int /*<<< orphan*/ * ets_tc_tsa_tbl; int /*<<< orphan*/ * ets_tc_bw_tbl; scalar_t__ max_ets_tc; scalar_t__ ets_enabled; scalar_t__ ets_cbs; scalar_t__ ets_willing; } ;
struct dcbx_ets_feature {int flags; int* pri_tc_tbl; void** tc_tsa_tbl; void** tc_bw_tbl; } ;

/* Variables and functions */
 int DCBX_ETS_CBS_MASK ; 
 int DCBX_ETS_ENABLED_MASK ; 
 int DCBX_ETS_MAX_TCS_MASK ; 
 int DCBX_ETS_MAX_TCS_OFFSET ; 
 int DCBX_ETS_WILLING_MASK ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int,void*,void*,void*,void*) ; 
 int ECORE_MAX_PFC_PRIORITIES ; 
 int /*<<< orphan*/  ECORE_MSG_DCB ; 
 void* OSAL_CPU_TO_BE32 (void*) ; 

__attribute__((used)) static void
ecore_dcbx_set_ets_data(struct ecore_hwfn *p_hwfn,
			struct dcbx_ets_feature *p_ets,
			struct ecore_dcbx_params *p_params)
{
	u8 *bw_map, *tsa_map;
	u32 val;
	int i;

	if (p_params->ets_willing)
		p_ets->flags |= DCBX_ETS_WILLING_MASK;
	else
		p_ets->flags &= ~DCBX_ETS_WILLING_MASK;

	if (p_params->ets_cbs)
		p_ets->flags |= DCBX_ETS_CBS_MASK;
	else
		p_ets->flags &= ~DCBX_ETS_CBS_MASK;

	if (p_params->ets_enabled)
		p_ets->flags |= DCBX_ETS_ENABLED_MASK;
	else
		p_ets->flags &= ~DCBX_ETS_ENABLED_MASK;

	p_ets->flags &= ~DCBX_ETS_MAX_TCS_MASK;
	p_ets->flags |= (u32)p_params->max_ets_tc << DCBX_ETS_MAX_TCS_OFFSET;

	bw_map = (u8 *)&p_ets->tc_bw_tbl[0];
	tsa_map = (u8 *)&p_ets->tc_tsa_tbl[0];
	p_ets->pri_tc_tbl[0] = 0;
	for (i = 0; i < ECORE_MAX_PFC_PRIORITIES; i++) {
		bw_map[i] = p_params->ets_tc_bw_tbl[i];
		tsa_map[i] = p_params->ets_tc_tsa_tbl[i];
		/* Copy the priority value to the corresponding 4 bits in the
		 * traffic class table.
		 */
		val = (((u32)p_params->ets_pri_tc_tbl[i]) << ((7 - i) * 4));
		p_ets->pri_tc_tbl[0] |= val;
	}
	for (i = 0; i < 2; i++) {
		p_ets->tc_bw_tbl[i] = OSAL_CPU_TO_BE32(p_ets->tc_bw_tbl[i]);
		p_ets->tc_tsa_tbl[i] = OSAL_CPU_TO_BE32(p_ets->tc_tsa_tbl[i]);
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_DCB,
		   "flags = 0x%x pri_tc = 0x%x tc_bwl[] = {0x%x, 0x%x} tc_tsa = {0x%x, 0x%x}\n",
		   p_ets->flags, p_ets->pri_tc_tbl[0], p_ets->tc_bw_tbl[0],
		   p_ets->tc_bw_tbl[1], p_ets->tc_tsa_tbl[0],
		   p_ets->tc_tsa_tbl[1]);
}