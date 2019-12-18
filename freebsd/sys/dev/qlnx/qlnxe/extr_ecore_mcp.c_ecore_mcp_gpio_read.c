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
typedef  int u32 ;
typedef  int u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int DRV_MB_PARAM_GPIO_NUMBER_OFFSET ; 
 int /*<<< orphan*/  DRV_MSG_CODE_GPIO_READ ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 int FW_MSG_CODE_GPIO_OK ; 
 int FW_MSG_CODE_MASK ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,int*,int*) ; 

enum _ecore_status_t ecore_mcp_gpio_read(struct ecore_hwfn *p_hwfn,
					 struct ecore_ptt *p_ptt,
					 u16 gpio, u32 *gpio_val)
{
	enum _ecore_status_t rc = ECORE_SUCCESS;
	u32 drv_mb_param = 0, rsp;

	drv_mb_param = (gpio << DRV_MB_PARAM_GPIO_NUMBER_OFFSET);

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_GPIO_READ,
			   drv_mb_param, &rsp, gpio_val);

	if (rc != ECORE_SUCCESS)
		return rc;

	if ((rsp & FW_MSG_CODE_MASK) != FW_MSG_CODE_GPIO_OK)
		return ECORE_UNKNOWN_ERROR;

	return ECORE_SUCCESS;
}