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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ecore_vf_info {scalar_t__ concrete_fid; } ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {scalar_t__ concrete_fid; } ;
struct ecore_hwfn {TYPE_1__ hw_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_REG_VF_CONFIGURATION ; 
 int /*<<< orphan*/  IGU_VF_CONF_MSI_MSIX_EN ; 
 int /*<<< orphan*/  ecore_fid_pretend (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_iov_vf_igu_set_int(struct ecore_hwfn		*p_hwfn,
				     struct ecore_ptt		*p_ptt,
				     struct ecore_vf_info	*vf,
				     bool			enable)
{
	u32 igu_vf_conf;

	ecore_fid_pretend(p_hwfn, p_ptt, (u16)vf->concrete_fid);

	igu_vf_conf = ecore_rd(p_hwfn, p_ptt, IGU_REG_VF_CONFIGURATION);

	if (enable) {
		igu_vf_conf |= IGU_VF_CONF_MSI_MSIX_EN;
	} else {
		igu_vf_conf &= ~IGU_VF_CONF_MSI_MSIX_EN;
	}

	ecore_wr(p_hwfn, p_ptt, IGU_REG_VF_CONFIGURATION, igu_vf_conf);

	/* unpretend */
	ecore_fid_pretend(p_hwfn, p_ptt, (u16)p_hwfn->hw_info.concrete_fid);
}