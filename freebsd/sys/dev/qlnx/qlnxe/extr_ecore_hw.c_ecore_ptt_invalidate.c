#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct ecore_ptt {TYPE_2__ pxp; } ;
struct ecore_hwfn {TYPE_1__* p_ptt_pool; } ;
struct TYPE_3__ {struct ecore_ptt* ptts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_BAR_INVALID_OFFSET ; 
 int PXP_EXTERNAL_BAR_PF_WINDOW_NUM ; 

void ecore_ptt_invalidate(struct ecore_hwfn *p_hwfn)
{
	struct ecore_ptt *p_ptt;
	int i;

	for (i = 0; i < PXP_EXTERNAL_BAR_PF_WINDOW_NUM; i++) {
		p_ptt = &p_hwfn->p_ptt_pool->ptts[i];
		p_ptt->pxp.offset = ECORE_BAR_INVALID_OFFSET;
	}
}