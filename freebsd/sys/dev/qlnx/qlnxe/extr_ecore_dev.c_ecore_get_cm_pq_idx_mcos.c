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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PQ_FLAGS_MCOS ; 
 scalar_t__ ecore_get_cm_pq_idx (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_init_qm_get_num_tcs (struct ecore_hwfn*) ; 

u16 ecore_get_cm_pq_idx_mcos(struct ecore_hwfn *p_hwfn, u8 tc)
{
	u8 max_tc = ecore_init_qm_get_num_tcs(p_hwfn);

	if (tc > max_tc)
		DP_ERR(p_hwfn, "tc %d must be smaller than %d\n", tc, max_tc);

	return ecore_get_cm_pq_idx(p_hwfn, PQ_FLAGS_MCOS) + tc;
}