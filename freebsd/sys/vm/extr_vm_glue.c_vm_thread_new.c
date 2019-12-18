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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct thread {int td_kstack_pages; scalar_t__ td_kstack; int /*<<< orphan*/ * td_kstack_obj; } ;
struct TYPE_2__ {int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_PREF (int /*<<< orphan*/ ) ; 
 int KSTACK_MAX_PAGES ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domain ; 
 int /*<<< orphan*/ * kstack_cache ; 
 int kstack_pages ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 scalar_t__ uma_zalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_thread_stack_create (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 

int
vm_thread_new(struct thread *td, int pages)
{
	vm_object_t ksobj;
	vm_offset_t ks;

	/* Bounds check */
	if (pages <= 1)
		pages = kstack_pages;
	else if (pages > KSTACK_MAX_PAGES)
		pages = KSTACK_MAX_PAGES;

	ks = 0;
	ksobj = NULL;
	if (pages == kstack_pages && kstack_cache != NULL) {
		ks = (vm_offset_t)uma_zalloc(kstack_cache, M_NOWAIT);
		if (ks != 0) 
			ksobj = PHYS_TO_VM_PAGE(pmap_kextract(ks))->object;
	}

	/*
	 * Ensure that kstack objects can draw pages from any memory
	 * domain.  Otherwise a local memory shortage can block a process
	 * swap-in.
	 */
	if (ks == 0)
		ks = vm_thread_stack_create(DOMAINSET_PREF(PCPU_GET(domain)),
		    &ksobj, pages);
	if (ks == 0)
		return (0);
	td->td_kstack_obj = ksobj;
	td->td_kstack = ks;
	td->td_kstack_pages = pages;
	return (1);
}