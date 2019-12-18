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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {TYPE_1__* p_dev; } ;
struct coalescing_timeset {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  osal_size_t ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ int_coalescing_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  COALESCING_TIMESET_TIMESET ; 
 int /*<<< orphan*/  COALESCING_TIMESET_VALID ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 scalar_t__ ECORE_COAL_MODE_ENABLE ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEMSET (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_memcpy_to (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_set_coalesce(struct ecore_hwfn *p_hwfn,
					       struct ecore_ptt *p_ptt,
					       u32 hw_addr, void *p_eth_qzone,
					       osal_size_t eth_qzone_size,
					       u8 timeset)
{
	struct coalescing_timeset *p_coal_timeset;

	if (p_hwfn->p_dev->int_coalescing_mode != ECORE_COAL_MODE_ENABLE) {
		DP_NOTICE(p_hwfn, true,
			  "Coalescing configuration not enabled\n");
		return ECORE_INVAL;
	}

	p_coal_timeset = p_eth_qzone;
	OSAL_MEMSET(p_eth_qzone, 0, eth_qzone_size);
	SET_FIELD(p_coal_timeset->value, COALESCING_TIMESET_TIMESET, timeset);
	SET_FIELD(p_coal_timeset->value, COALESCING_TIMESET_VALID, 1);
	ecore_memcpy_to(p_hwfn, p_ptt, hw_addr, p_eth_qzone, eth_qzone_size);

	return ECORE_SUCCESS;
}