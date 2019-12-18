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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ ECORE_IS_E4 (int /*<<< orphan*/ ) ; 
 int ecore_llh_add_filter_e4 (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_llh_add_filter_e5 (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_llh_add_filter(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
		     u8 abs_ppfid, u8 filter_idx, u8 filter_prot_type, u32 high,
		     u32 low)
{
	if (ECORE_IS_E4(p_hwfn->p_dev))
		return ecore_llh_add_filter_e4(p_hwfn, p_ptt, abs_ppfid,
					       filter_idx, filter_prot_type,
					       high, low);
	else /* E5 */
		return ecore_llh_add_filter_e5(p_hwfn, p_ptt, abs_ppfid,
					       filter_idx, filter_prot_type,
					       high, low);
}