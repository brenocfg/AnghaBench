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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct thread {int td_kstack_pages; int /*<<< orphan*/  td_kstack; int /*<<< orphan*/  td_kstack_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_LAUNDRY ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_thread_swapout (struct thread*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_qremove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_lookup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_thread_swapout(struct thread *td)
{
	vm_object_t ksobj;
	vm_page_t m;
	int i, pages;

	cpu_thread_swapout(td);
	pages = td->td_kstack_pages;
	ksobj = td->td_kstack_obj;
	pmap_qremove(td->td_kstack, pages);
	VM_OBJECT_WLOCK(ksobj);
	for (i = 0; i < pages; i++) {
		m = vm_page_lookup(ksobj, i);
		if (m == NULL)
			panic("vm_thread_swapout: kstack already missing?");
		vm_page_dirty(m);
		vm_page_unwire(m, PQ_LAUNDRY);
	}
	VM_OBJECT_WUNLOCK(ksobj);
}