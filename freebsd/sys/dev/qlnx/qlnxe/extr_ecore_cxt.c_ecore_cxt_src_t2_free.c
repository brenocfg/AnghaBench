#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {size_t t2_num_pages; TYPE_1__* t2; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  p_phys; scalar_t__ p_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* OSAL_NULL ; 

__attribute__((used)) static void ecore_cxt_src_t2_free(struct ecore_hwfn *p_hwfn)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 i;

	if (!p_mngr->t2)
		return;

	for (i = 0; i < p_mngr->t2_num_pages; i++)
		if (p_mngr->t2[i].p_virt)
			OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
					       p_mngr->t2[i].p_virt,
					       p_mngr->t2[i].p_phys,
					       p_mngr->t2[i].size);

	OSAL_FREE(p_hwfn->p_dev, p_mngr->t2);
	p_mngr->t2 = OSAL_NULL;
}