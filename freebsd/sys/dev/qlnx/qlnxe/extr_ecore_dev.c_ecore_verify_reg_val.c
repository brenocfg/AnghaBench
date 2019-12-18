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
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_verify_reg_val(struct ecore_hwfn *p_hwfn,
						 struct ecore_ptt *p_ptt,
						 u32 addr, u32 expected_val)
{
	u32 val = ecore_rd(p_hwfn, p_ptt, addr);

	if (val != expected_val) {
		DP_NOTICE(p_hwfn, true,
			  "Value at address 0x%08x is 0x%08x while the expected value is 0x%08x\n",
			  addr, val, expected_val);
		return ECORE_UNKNOWN_ERROR;
	}

	return ECORE_SUCCESS;
}