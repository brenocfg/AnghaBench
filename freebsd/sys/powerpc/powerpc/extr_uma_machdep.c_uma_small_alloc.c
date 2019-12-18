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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int M_NODUMP ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_ZERO ; 
 scalar_t__ PHYS_TO_DMAP (scalar_t__) ; 
 int /*<<< orphan*/  UMA_SLAB_PRIV ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 scalar_t__ VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_add_page (scalar_t__) ; 
 int /*<<< orphan*/  hw_direct_map ; 
 int /*<<< orphan*/  hw_uma_mdpages ; 
 int malloc2vm_flags (int) ; 
 int /*<<< orphan*/  pmap_kenter (scalar_t__,scalar_t__) ; 
 TYPE_1__* vm_page_alloc_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void *
uma_small_alloc(uma_zone_t zone, vm_size_t bytes, int domain, u_int8_t *flags,
    int wait)
{
	void *va;
	vm_paddr_t pa;
	vm_page_t m;
	
	*flags = UMA_SLAB_PRIV;

	m = vm_page_alloc_domain(NULL, 0, domain,
	    malloc2vm_flags(wait) | VM_ALLOC_WIRED | VM_ALLOC_NOOBJ);
	if (m == NULL) 
		return (NULL);

	pa = VM_PAGE_TO_PHYS(m);

	/* On book-e sizeof(void *) < sizeof(vm_paddr_t) */
	if ((vm_offset_t)pa != pa)
		return (NULL);

#ifdef __powerpc64__
	if ((wait & M_NODUMP) == 0)
		dump_add_page(pa);
#endif

	if (!hw_direct_map) {
		pmap_kenter(pa, pa);
		va = (void *)(vm_offset_t)pa;
	} else {
		va = (void *)(vm_offset_t)PHYS_TO_DMAP(pa);
	}

	if ((wait & M_ZERO) && (m->flags & PG_ZERO) == 0)
		bzero(va, PAGE_SIZE);
	atomic_add_int(&hw_uma_mdpages, 1);

	return (va);
}