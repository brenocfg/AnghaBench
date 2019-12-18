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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum ecore_ov_eswitch { ____Placeholder_ecore_ov_eswitch } ecore_ov_eswitch ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_ESWITCH_MODE_NONE ; 
 int /*<<< orphan*/  DRV_MB_PARAM_ESWITCH_MODE_VEB ; 
 int /*<<< orphan*/  DRV_MB_PARAM_ESWITCH_MODE_VEPA ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_ESWITCH_MODE ; 
 int ECORE_INVAL ; 
#define  ECORE_OV_ESWITCH_NONE 130 
#define  ECORE_OV_ESWITCH_VEB 129 
#define  ECORE_OV_ESWITCH_VEPA 128 
 int ECORE_SUCCESS ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t
ecore_mcp_ov_update_eswitch(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			    enum ecore_ov_eswitch eswitch)
{
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	enum _ecore_status_t rc;

	switch (eswitch) {
	case ECORE_OV_ESWITCH_NONE:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_NONE;
		break;
	case ECORE_OV_ESWITCH_VEB:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_VEB;
		break;
	case ECORE_OV_ESWITCH_VEPA:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_VEPA;
		break;
	default:
		DP_ERR(p_hwfn, "Invalid eswitch mode %d\n", eswitch);
		return ECORE_INVAL;
	}

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_ESWITCH_MODE,
			   drv_mb_param, &resp, &param);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "Failed to send eswitch mode, rc = %d\n", rc);

	return rc;
}