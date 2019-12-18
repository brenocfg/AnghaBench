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
struct TYPE_2__ {int /*<<< orphan*/  p_igu_info; } ;
struct ecore_hwfn {TYPE_1__ hw_info; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  ecore_ptt_pool_free (struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_hw_hwfn_free(struct ecore_hwfn *p_hwfn)
{
	ecore_ptt_pool_free(p_hwfn);
	OSAL_FREE(p_hwfn->p_dev, p_hwfn->hw_info.p_igu_info);
	p_hwfn->hw_info.p_igu_info = OSAL_NULL;
}