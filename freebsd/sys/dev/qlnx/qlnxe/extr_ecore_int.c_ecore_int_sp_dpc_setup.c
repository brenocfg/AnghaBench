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
struct ecore_hwfn {int b_sp_dpc_enabled; int /*<<< orphan*/  sp_dpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_DPC_INIT (int /*<<< orphan*/ ,struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_int_sp_dpc_setup(struct ecore_hwfn *p_hwfn)
{
	OSAL_DPC_INIT(p_hwfn->sp_dpc, p_hwfn);
	p_hwfn->b_sp_dpc_enabled = true;
}