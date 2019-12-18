#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct sysentvec {size_t sv_shared_page_len; scalar_t__ sv_shared_page_base; scalar_t__ sv_usrstack; int /*<<< orphan*/  sv_shared_page_obj; scalar_t__ sv_maxuser; } ;
struct TYPE_4__ {int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 int /*<<< orphan*/  OBJT_PHYS ; 
 size_t PAGE_SIZE ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_BITS_ALL ; 
 int /*<<< orphan*/  VM_PROT_DEFAULT ; 
 size_t howmany (size_t,size_t) ; 
 scalar_t__ kva_alloc (size_t) ; 
 int /*<<< orphan*/  kva_free (scalar_t__,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_qenter (scalar_t__,TYPE_1__**,int) ; 
 int /*<<< orphan*/  pmap_qremove (scalar_t__,int) ; 
 TYPE_1__* vm_page_grab (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
cloudabi_vdso_init(struct sysentvec *sv, char *begin, char *end)
{
	vm_page_t m;
	vm_object_t obj;
	vm_offset_t addr;
	size_t i, pages, pages_length, vdso_length;

	/* Determine the number of pages needed to store the vDSO. */
	vdso_length = end - begin;
	pages = howmany(vdso_length, PAGE_SIZE);
	pages_length = pages * PAGE_SIZE;

	/* Allocate a VM object and fill it with the vDSO. */
	obj = vm_pager_allocate(OBJT_PHYS, 0, pages_length,
	    VM_PROT_DEFAULT, 0, NULL);
	addr = kva_alloc(PAGE_SIZE);
	for (i = 0; i < pages; ++i) {
		VM_OBJECT_WLOCK(obj);
		m = vm_page_grab(obj, i, VM_ALLOC_NOBUSY | VM_ALLOC_ZERO);
		m->valid = VM_PAGE_BITS_ALL;
		VM_OBJECT_WUNLOCK(obj);

		pmap_qenter(addr, &m, 1);
		memcpy((void *)addr, begin + i * PAGE_SIZE,
		    MIN(vdso_length - i * PAGE_SIZE, PAGE_SIZE));
		pmap_qremove(addr, 1);
	}
	kva_free(addr, PAGE_SIZE);

	/*
	 * Place the vDSO at the top of the address space. The user
	 * stack can start right below it.
	 */
	sv->sv_shared_page_base = sv->sv_maxuser - pages_length;
	sv->sv_shared_page_len = pages_length;
	sv->sv_shared_page_obj = obj;
	sv->sv_usrstack = sv->sv_shared_page_base;
}