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
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
struct vm_phys_fictitious_seg {scalar_t__ start; TYPE_1__* first_page; scalar_t__ end; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PG_FICTITIOUS ; 
 struct vm_phys_fictitious_seg* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vm_phys_fictitious_seg*) ; 
 size_t atop (scalar_t__) ; 
 int /*<<< orphan*/  fict_tree ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_phys_fictitious_reg_lock ; 
 int /*<<< orphan*/  vm_phys_fictitious_tree ; 

vm_page_t
vm_phys_fictitious_to_vm_page(vm_paddr_t pa)
{
	struct vm_phys_fictitious_seg tmp, *seg;
	vm_page_t m;

	m = NULL;
	tmp.start = pa;
	tmp.end = 0;

	rw_rlock(&vm_phys_fictitious_reg_lock);
	seg = RB_FIND(fict_tree, &vm_phys_fictitious_tree, &tmp);
	rw_runlock(&vm_phys_fictitious_reg_lock);
	if (seg == NULL)
		return (NULL);

	m = &seg->first_page[atop(pa - seg->start)];
	KASSERT((m->flags & PG_FICTITIOUS) != 0, ("%p not fictitious", m));

	return (m);
}