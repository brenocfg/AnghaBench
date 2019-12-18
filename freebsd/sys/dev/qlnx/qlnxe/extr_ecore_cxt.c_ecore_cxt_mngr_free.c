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
struct ecore_hwfn {TYPE_1__* p_cxt_mngr; int /*<<< orphan*/  p_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  OSAL_MUTEX_DEALLOC (int /*<<< orphan*/ *) ; 
 TYPE_1__* OSAL_NULL ; 
 int /*<<< orphan*/  ecore_cid_map_free (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_cxt_src_t2_free (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ilt_shadow_free (struct ecore_hwfn*) ; 

void ecore_cxt_mngr_free(struct ecore_hwfn *p_hwfn)
{
	if (!p_hwfn->p_cxt_mngr)
		return;

	ecore_cid_map_free(p_hwfn);
	ecore_cxt_src_t2_free(p_hwfn);
	ecore_ilt_shadow_free(p_hwfn);
#ifdef CONFIG_ECORE_LOCK_ALLOC
	OSAL_MUTEX_DEALLOC(&p_hwfn->p_cxt_mngr->mutex);
#endif
	OSAL_FREE(p_hwfn->p_dev, p_hwfn->p_cxt_mngr);

	p_hwfn->p_cxt_mngr = OSAL_NULL;
}