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
typedef  int u16 ;
struct ecore_hwfn {TYPE_1__* pf_iov_info; } ;
struct TYPE_2__ {unsigned long long* pending_flr; } ;

/* Variables and functions */

bool ecore_iov_is_vf_pending_flr(struct ecore_hwfn *p_hwfn,
				 u16		   rel_vf_id)
{
	return !!(p_hwfn->pf_iov_info->pending_flr[rel_vf_id / 64] &
		  (1ULL << (rel_vf_id % 64)));
}