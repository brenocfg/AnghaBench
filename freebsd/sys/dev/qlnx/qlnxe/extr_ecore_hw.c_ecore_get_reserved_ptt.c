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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {TYPE_1__* p_ptt_pool; } ;
typedef  enum reserved_ptts { ____Placeholder_reserved_ptts } reserved_ptts ;
struct TYPE_2__ {struct ecore_ptt* ptts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 struct ecore_ptt* OSAL_NULL ; 
 int RESERVED_PTT_MAX ; 

struct ecore_ptt *ecore_get_reserved_ptt(struct ecore_hwfn *p_hwfn,
					 enum reserved_ptts ptt_idx)
{
	if (ptt_idx >= RESERVED_PTT_MAX) {
		DP_NOTICE(p_hwfn, true,
			  "Requested PTT %d is out of range\n", ptt_idx);
		return OSAL_NULL;
	}

	return &p_hwfn->p_ptt_pool->ptts[ptt_idx];
}