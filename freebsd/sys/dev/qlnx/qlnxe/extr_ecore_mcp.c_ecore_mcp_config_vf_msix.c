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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ ECORE_IS_BB (int /*<<< orphan*/ ) ; 
 int ecore_mcp_config_vf_msix_ah (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int ecore_mcp_config_vf_msix_bb (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_mcp_config_vf_msix(struct ecore_hwfn *p_hwfn,
					      struct ecore_ptt *p_ptt,
					      u8 vf_id, u8 num)
{
	if (ECORE_IS_BB(p_hwfn->p_dev))
		return ecore_mcp_config_vf_msix_bb(p_hwfn, p_ptt, vf_id, num);
	else
		return ecore_mcp_config_vf_msix_ah(p_hwfn, p_ptt, num);
}