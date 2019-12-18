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
typedef  enum ecore_led_mode { ____Placeholder_ecore_led_mode } ecore_led_mode ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_SET_LED_MODE_OFF ; 
 int /*<<< orphan*/  DRV_MB_PARAM_SET_LED_MODE_ON ; 
 int /*<<< orphan*/  DRV_MB_PARAM_SET_LED_MODE_OPER ; 
 int /*<<< orphan*/  DRV_MSG_CODE_SET_LED_MODE ; 
 int ECORE_INVAL ; 
#define  ECORE_LED_MODE_OFF 130 
#define  ECORE_LED_MODE_ON 129 
#define  ECORE_LED_MODE_RESTORE 128 
 int ECORE_SUCCESS ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t ecore_mcp_set_led(struct ecore_hwfn *p_hwfn,
				       struct ecore_ptt *p_ptt,
				       enum ecore_led_mode mode)
{
	u32 resp = 0, param = 0, drv_mb_param;
	enum _ecore_status_t rc;

	switch (mode) {
	case ECORE_LED_MODE_ON:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_ON;
		break;
	case ECORE_LED_MODE_OFF:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_OFF;
		break;
	case ECORE_LED_MODE_RESTORE:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_OPER;
		break;
	default:
		DP_NOTICE(p_hwfn, true, "Invalid LED mode %d\n", mode);
		return ECORE_INVAL;
	}

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_SET_LED_MODE,
			   drv_mb_param, &resp, &param);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");

	return rc;
}