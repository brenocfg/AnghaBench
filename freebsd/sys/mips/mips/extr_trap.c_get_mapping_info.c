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
typedef  int vm_offset_t ;
struct proc {TYPE_1__* p_vmspace; } ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_4__ {scalar_t__* pm_segtab; } ;
struct TYPE_3__ {TYPE_2__ vm_pmap; } ;

/* Variables and functions */
 int NPDEPG ; 
 int SEGSHIFT ; 
 struct proc* curproc ; 
 int /*<<< orphan*/ * pmap_pte (TYPE_2__*,int) ; 

__attribute__((used)) static void
get_mapping_info(vm_offset_t va, pd_entry_t **pdepp, pt_entry_t **ptepp)
{
	pt_entry_t *ptep;
	pd_entry_t *pdep;
	struct proc *p = curproc;

	pdep = (&(p->p_vmspace->vm_pmap.pm_segtab[(va >> SEGSHIFT) & (NPDEPG - 1)]));
	if (*pdep)
		ptep = pmap_pte(&p->p_vmspace->vm_pmap, va);
	else
		ptep = (pt_entry_t *)0;

	*pdepp = pdep;
	*ptepp = ptep;
}