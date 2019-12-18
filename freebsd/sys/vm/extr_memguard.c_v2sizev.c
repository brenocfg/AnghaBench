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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
struct TYPE_4__ {TYPE_1__ memguard; } ;
struct vm_page {scalar_t__ queue; TYPE_2__ plinks; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct vm_page* PHYS_TO_VM_PAGE (scalar_t__) ; 
 scalar_t__ PQ_NONE ; 
 int /*<<< orphan*/  panic (char*,void*) ; 
 scalar_t__ pmap_kextract (scalar_t__) ; 
 scalar_t__ vm_page_wired (struct vm_page*) ; 

__attribute__((used)) static u_long *
v2sizev(vm_offset_t va)
{
	vm_paddr_t pa;
	struct vm_page *p;

	pa = pmap_kextract(va);
	if (pa == 0)
		panic("MemGuard detected double-free of %p", (void *)va);
	p = PHYS_TO_VM_PAGE(pa);
	KASSERT(vm_page_wired(p) && p->queue == PQ_NONE,
	    ("MEMGUARD: Expected wired page %p in vtomgfifo!", p));
	return (&p->plinks.memguard.v);
}