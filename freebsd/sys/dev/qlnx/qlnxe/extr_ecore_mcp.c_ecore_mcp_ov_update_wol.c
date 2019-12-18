#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_4__ {scalar_t__ b_wol_support; } ;
struct ecore_hwfn {TYPE_1__* p_dev; TYPE_2__ hw_info; } ;
typedef  enum ecore_ov_wol { ____Placeholder_ecore_ov_wol } ecore_ov_wol ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_3__ {scalar_t__ wol_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_WOL_DEFAULT ; 
 int /*<<< orphan*/  DRV_MB_PARAM_WOL_DISABLED ; 
 int /*<<< orphan*/  DRV_MB_PARAM_WOL_ENABLED ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_WOL ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
#define  ECORE_OV_WOL_DEFAULT 130 
#define  ECORE_OV_WOL_DISABLED 129 
#define  ECORE_OV_WOL_ENABLED 128 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_WOL_SUPPORT_NONE ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t
ecore_mcp_ov_update_wol(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			enum ecore_ov_wol wol)
{
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	enum _ecore_status_t rc;

	if (p_hwfn->hw_info.b_wol_support == ECORE_WOL_SUPPORT_NONE) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
			   "Can't change WoL configuration when WoL isn't supported\n");
		return ECORE_INVAL;
	}

	switch (wol) {
	case ECORE_OV_WOL_DEFAULT:
		drv_mb_param = DRV_MB_PARAM_WOL_DEFAULT;
		break;
	case ECORE_OV_WOL_DISABLED:
		drv_mb_param = DRV_MB_PARAM_WOL_DISABLED;
		break;
	case ECORE_OV_WOL_ENABLED:
		drv_mb_param = DRV_MB_PARAM_WOL_ENABLED;
		break;
	default:
		DP_ERR(p_hwfn, "Invalid wol state %d\n", wol);
		return ECORE_INVAL;
	}

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_WOL,
			   drv_mb_param, &resp, &param);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "Failed to send wol mode, rc = %d\n", rc);

	/* Store the WoL update for a future unload */
	p_hwfn->p_dev->wol_config = (u8)wol;

	return rc;
}