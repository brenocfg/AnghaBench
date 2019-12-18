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
struct ecore_hwfn {int /*<<< orphan*/  sp_dpc; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_DPC_ALLOC (struct ecore_hwfn*) ; 

__attribute__((used)) static enum _ecore_status_t ecore_int_sp_dpc_alloc(struct ecore_hwfn *p_hwfn)
{
	p_hwfn->sp_dpc = OSAL_DPC_ALLOC(p_hwfn);
	if (!p_hwfn->sp_dpc)
		return ECORE_NOMEM;

	return ECORE_SUCCESS;
}