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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {TYPE_1__* p_dev; } ;
typedef  enum ecore_int_mode { ____Placeholder_ecore_int_mode } ecore_int_mode ;
struct TYPE_2__ {int int_mode; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_FPGA (TYPE_1__*) ; 
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
#define  ECORE_INT_MODE_INTA 131 
#define  ECORE_INT_MODE_MSI 130 
#define  ECORE_INT_MODE_MSIX 129 
#define  ECORE_INT_MODE_POLL 128 
 int IGU_PF_CONF_ATTN_BIT_EN ; 
 int IGU_PF_CONF_FUNC_EN ; 
 int IGU_PF_CONF_INT_LINE_EN ; 
 int IGU_PF_CONF_MSI_MSIX_EN ; 
 int IGU_PF_CONF_SINGLE_ISR_EN ; 
 int /*<<< orphan*/  IGU_REG_PF_CONFIGURATION ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

void ecore_int_igu_enable_int(struct ecore_hwfn *p_hwfn,
			      struct ecore_ptt	*p_ptt,
			      enum ecore_int_mode int_mode)
{
	u32 igu_pf_conf = IGU_PF_CONF_FUNC_EN | IGU_PF_CONF_ATTN_BIT_EN;

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_FPGA(p_hwfn->p_dev)) {
		DP_INFO(p_hwfn, "FPGA - don't enable ATTN generation in IGU\n");
		igu_pf_conf &= ~IGU_PF_CONF_ATTN_BIT_EN;
	}
#endif

	p_hwfn->p_dev->int_mode = int_mode;
	switch (p_hwfn->p_dev->int_mode) {
	case ECORE_INT_MODE_INTA:
		igu_pf_conf |= IGU_PF_CONF_INT_LINE_EN;
		igu_pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
		break;

	case ECORE_INT_MODE_MSI:
		igu_pf_conf |= IGU_PF_CONF_MSI_MSIX_EN;
		igu_pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
		break;

	case ECORE_INT_MODE_MSIX:
		igu_pf_conf |= IGU_PF_CONF_MSI_MSIX_EN;
		break;
	case ECORE_INT_MODE_POLL:
		break;
	}

	ecore_wr(p_hwfn, p_ptt, IGU_REG_PF_CONFIGURATION, igu_pf_conf);
}