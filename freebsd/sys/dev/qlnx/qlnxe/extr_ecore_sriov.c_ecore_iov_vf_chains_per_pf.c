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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ max_chains_per_vf; } ;
struct ecore_hwfn {TYPE_1__ hw_info; } ;

/* Variables and functions */
 scalar_t__ ECORE_MAX_VF_CHAINS_PER_PF ; 

u8 ecore_iov_vf_chains_per_pf(struct ecore_hwfn *p_hwfn)
{
	u8 max_chains_per_vf = p_hwfn->hw_info.max_chains_per_vf;

	max_chains_per_vf = (max_chains_per_vf) ? max_chains_per_vf
						: ECORE_MAX_VF_CHAINS_PER_PF;

	return max_chains_per_vf;
}