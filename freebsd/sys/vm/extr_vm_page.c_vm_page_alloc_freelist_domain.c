#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  u_int ;
struct vm_domain {int dummy; } ;
struct TYPE_6__ {int ref_count; int /*<<< orphan*/  oflags; int /*<<< orphan*/  flags; scalar_t__ aflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_ZERO ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 struct vm_domain* VM_DOMAIN (int) ; 
 int /*<<< orphan*/  VM_FREEPOOL_DIRECT ; 
 int /*<<< orphan*/  VPO_UNMANAGED ; 
 scalar_t__ vm_domain_alloc_fail (struct vm_domain*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ vm_domain_allocate (struct vm_domain*,int,int) ; 
 int /*<<< orphan*/  vm_domain_free_lock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_free_unlock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_freecnt_inc (struct vm_domain*,int) ; 
 int /*<<< orphan*/  vm_page_alloc_check (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_dequeue (TYPE_1__*) ; 
 TYPE_1__* vm_phys_alloc_freelist_pages (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_wire_add (int) ; 

vm_page_t
vm_page_alloc_freelist_domain(int domain, int freelist, int req)
{
	struct vm_domain *vmd;
	vm_page_t m;
	u_int flags;

	m = NULL;
	vmd = VM_DOMAIN(domain);
again:
	if (vm_domain_allocate(vmd, req, 1)) {
		vm_domain_free_lock(vmd);
		m = vm_phys_alloc_freelist_pages(domain, freelist,
		    VM_FREEPOOL_DIRECT, 0);
		vm_domain_free_unlock(vmd);
		if (m == NULL)
			vm_domain_freecnt_inc(vmd, 1);
	}
	if (m == NULL) {
		if (vm_domain_alloc_fail(vmd, NULL, req))
			goto again;
		return (NULL);
	}
	vm_page_dequeue(m);
	vm_page_alloc_check(m);

	/*
	 * Initialize the page.  Only the PG_ZERO flag is inherited.
	 */
	m->aflags = 0;
	flags = 0;
	if ((req & VM_ALLOC_ZERO) != 0)
		flags = PG_ZERO;
	m->flags &= flags;
	if ((req & VM_ALLOC_WIRED) != 0) {
		/*
		 * The page lock is not required for wiring a page that does
		 * not belong to an object.
		 */
		vm_wire_add(1);
		m->ref_count = 1;
	}
	/* Unmanaged pages don't use "act_count". */
	m->oflags = VPO_UNMANAGED;
	return (m);
}