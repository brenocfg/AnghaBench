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
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_PF_L2_QUE ; 
 scalar_t__ FEAT_NUM (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

u32 ecore_rdma_get_sb_id(struct ecore_hwfn *p_hwfn, u32 rel_sb_id)
{
	/* first sb id for RoCE is after all the l2 sb */
	return FEAT_NUM(p_hwfn, ECORE_PF_L2_QUE) + rel_sb_id;
}