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
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_PQ ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ECORE_VPORT ; 
 scalar_t__ RESC_NUM (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_init_qm_get_num_pqs (struct ecore_hwfn*) ; 
 scalar_t__ ecore_init_qm_get_num_vports (struct ecore_hwfn*) ; 

__attribute__((used)) static enum _ecore_status_t ecore_init_qm_sanity(struct ecore_hwfn *p_hwfn)
{
	if (ecore_init_qm_get_num_vports(p_hwfn) > RESC_NUM(p_hwfn, ECORE_VPORT)) {
		DP_ERR(p_hwfn, "requested amount of vports exceeds resource\n");
		return ECORE_INVAL;
	}

	if (ecore_init_qm_get_num_pqs(p_hwfn) > RESC_NUM(p_hwfn, ECORE_PQ)) {
		DP_ERR(p_hwfn, "requested amount of pqs exceeds resource\n");
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}