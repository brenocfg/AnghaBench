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
typedef  scalar_t__ u32 ;
struct ecore_resc_lock_params {scalar_t__ retry_num; scalar_t__ b_granted; int /*<<< orphan*/  retry_interval; scalar_t__ sleep_b4_retry; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MSLEEP (scalar_t__) ; 
 int /*<<< orphan*/  OSAL_UDELAY (int /*<<< orphan*/ ) ; 
 int __ecore_mcp_resc_lock (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_resc_lock_params*) ; 

enum _ecore_status_t
ecore_mcp_resc_lock(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
		    struct ecore_resc_lock_params *p_params)
{
	u32 retry_cnt = 0;
	enum _ecore_status_t rc;

	do {
		/* No need for an interval before the first iteration */
		if (retry_cnt) {
			if (p_params->sleep_b4_retry) {
				u32 retry_interval_in_ms =
					DIV_ROUND_UP(p_params->retry_interval,
						     1000);

				OSAL_MSLEEP(retry_interval_in_ms);
			} else {
				OSAL_UDELAY(p_params->retry_interval);
			}
		}

		rc = __ecore_mcp_resc_lock(p_hwfn, p_ptt, p_params);
		if (rc != ECORE_SUCCESS)
			return rc;

		if (p_params->b_granted)
			break;
	} while (retry_cnt++ < p_params->retry_num);

	return ECORE_SUCCESS;
}