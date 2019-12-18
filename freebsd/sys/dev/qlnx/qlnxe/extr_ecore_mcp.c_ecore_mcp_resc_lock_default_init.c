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
struct ecore_resc_unlock_params {int sleep_b4_retry; int resource; int /*<<< orphan*/  retry_interval; int /*<<< orphan*/  retry_num; int /*<<< orphan*/  timeout; } ;
struct ecore_resc_lock_params {int sleep_b4_retry; int resource; int /*<<< orphan*/  retry_interval; int /*<<< orphan*/  retry_num; int /*<<< orphan*/  timeout; } ;
typedef  enum ecore_resc_lock { ____Placeholder_ecore_resc_lock } ecore_resc_lock ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MCP_RESC_LOCK_RETRY_CNT_DFLT ; 
 int /*<<< orphan*/  ECORE_MCP_RESC_LOCK_RETRY_VAL_DFLT ; 
 int /*<<< orphan*/  ECORE_MCP_RESC_LOCK_TO_NONE ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_resc_unlock_params*,int) ; 
 struct ecore_resc_unlock_params* OSAL_NULL ; 

void ecore_mcp_resc_lock_default_init(struct ecore_resc_lock_params *p_lock,
				      struct ecore_resc_unlock_params *p_unlock,
				      enum ecore_resc_lock resource,
				      bool b_is_permanent)
{
	if (p_lock != OSAL_NULL) {
		OSAL_MEM_ZERO(p_lock, sizeof(*p_lock));

		/* Permanent resources don't require aging, and there's no
		 * point in trying to acquire them more than once since it's
		 * unexpected another entity would release them.
		 */
		if (b_is_permanent) {
			p_lock->timeout = ECORE_MCP_RESC_LOCK_TO_NONE;
		} else {
			p_lock->retry_num = ECORE_MCP_RESC_LOCK_RETRY_CNT_DFLT;
			p_lock->retry_interval =
					ECORE_MCP_RESC_LOCK_RETRY_VAL_DFLT;
			p_lock->sleep_b4_retry = true;
		}

		p_lock->resource = resource;
	}

	if (p_unlock != OSAL_NULL) {
		OSAL_MEM_ZERO(p_unlock, sizeof(*p_unlock));
		p_unlock->resource = resource;
	}
}