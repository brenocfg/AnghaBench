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
typedef  enum ecore_ov_driver_state { ____Placeholder_ecore_ov_driver_state } ecore_ov_driver_state ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_ACTIVE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_DISABLED ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_NOT_LOADED ; 
 int ECORE_INVAL ; 
#define  ECORE_OV_DRIVER_STATE_ACTIVE 130 
#define  ECORE_OV_DRIVER_STATE_DISABLED 129 
#define  ECORE_OV_DRIVER_STATE_NOT_LOADED 128 
 int ECORE_SUCCESS ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t
ecore_mcp_ov_update_driver_state(struct ecore_hwfn *p_hwfn,
				 struct ecore_ptt *p_ptt,
				 enum ecore_ov_driver_state drv_state)
{
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	enum _ecore_status_t rc;

	switch (drv_state) {
	case ECORE_OV_DRIVER_STATE_NOT_LOADED:
		drv_mb_param = DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_NOT_LOADED;
		break;
	case ECORE_OV_DRIVER_STATE_DISABLED:
		drv_mb_param = DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_DISABLED;
		break;
	case ECORE_OV_DRIVER_STATE_ACTIVE:
		drv_mb_param = DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE_ACTIVE;
		break;
	default:
		DP_NOTICE(p_hwfn, true,
			  "Invalid driver state %d\n", drv_state);
		return ECORE_INVAL;
	}

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_DRIVER_STATE,
			   drv_mb_param, &resp, &param);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "Failed to send driver state\n");

	return rc;
}