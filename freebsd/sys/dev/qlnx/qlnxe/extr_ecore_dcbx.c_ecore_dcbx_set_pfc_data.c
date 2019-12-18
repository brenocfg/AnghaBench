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
typedef  int u8 ;
typedef  int u32 ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_2__ {scalar_t__* prio; scalar_t__ max_tc; scalar_t__ enabled; scalar_t__ willing; } ;
struct ecore_dcbx_params {TYPE_1__ pfc; } ;

/* Variables and functions */
 int DCBX_PFC_CAPS_MASK ; 
 int DCBX_PFC_CAPS_OFFSET ; 
 int DCBX_PFC_ENABLED_MASK ; 
 int DCBX_PFC_ERROR_MASK ; 
 int DCBX_PFC_PRI_EN_BITMAP_MASK ; 
 int DCBX_PFC_PRI_EN_BITMAP_OFFSET ; 
 int DCBX_PFC_WILLING_MASK ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int ECORE_MAX_PFC_PRIORITIES ; 
 int /*<<< orphan*/  ECORE_MSG_DCB ; 

__attribute__((used)) static void
ecore_dcbx_set_pfc_data(struct ecore_hwfn *p_hwfn,
			u32 *pfc, struct ecore_dcbx_params *p_params)
{
	u8 pfc_map = 0;
	int i;

	*pfc &= ~DCBX_PFC_ERROR_MASK;

	if (p_params->pfc.willing)
		*pfc |= DCBX_PFC_WILLING_MASK;
	else
		*pfc &= ~DCBX_PFC_WILLING_MASK;

	if (p_params->pfc.enabled)
		*pfc |= DCBX_PFC_ENABLED_MASK;
	else
		*pfc &= ~DCBX_PFC_ENABLED_MASK;

	*pfc &= ~DCBX_PFC_CAPS_MASK;
	*pfc |= (u32)p_params->pfc.max_tc << DCBX_PFC_CAPS_OFFSET;

	for (i = 0; i < ECORE_MAX_PFC_PRIORITIES; i++)
		if (p_params->pfc.prio[i])
			pfc_map |= (1 << i);
	*pfc &= ~DCBX_PFC_PRI_EN_BITMAP_MASK;
	*pfc |= (pfc_map << DCBX_PFC_PRI_EN_BITMAP_OFFSET);

	DP_VERBOSE(p_hwfn, ECORE_MSG_DCB, "pfc = 0x%x\n", *pfc);
}