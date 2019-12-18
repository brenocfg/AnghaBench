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
struct ecore_hwfn {int /*<<< orphan*/  sp_dpc; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_NULL ; 

__attribute__((used)) static void ecore_int_sp_dpc_free(struct ecore_hwfn *p_hwfn)
{
	OSAL_FREE(p_hwfn->p_dev, p_hwfn->sp_dpc);
	p_hwfn->sp_dpc = OSAL_NULL;
}