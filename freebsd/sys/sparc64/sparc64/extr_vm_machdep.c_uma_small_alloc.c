#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_5__ {scalar_t__ color; scalar_t__* colors; } ;
struct TYPE_6__ {int flags; TYPE_1__ md; } ;

/* Variables and functions */
 scalar_t__ DCACHE_COLOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_ZERO ; 
 int /*<<< orphan*/  PMAP_STATS_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ TLB_PHYS_TO_DIRECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMA_SLAB_PRIV ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  cpu_block_zero (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ dcache_color_ignore ; 
 int /*<<< orphan*/  dcache_page_inval (int /*<<< orphan*/ ) ; 
 int malloc2vm_flags (int) ; 
 int /*<<< orphan*/  uma_nsmall_alloc ; 
 int /*<<< orphan*/  uma_nsmall_alloc_oc ; 
 TYPE_2__* vm_page_alloc_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void *
uma_small_alloc(uma_zone_t zone, vm_size_t bytes, int domain, u_int8_t *flags,
    int wait)
{
	vm_paddr_t pa;
	vm_page_t m;
	void *va;

	PMAP_STATS_INC(uma_nsmall_alloc);

	*flags = UMA_SLAB_PRIV;

	m = vm_page_alloc_domain(NULL, 0, domain,
	    malloc2vm_flags(wait) | VM_ALLOC_WIRED | VM_ALLOC_NOOBJ);
	if (m == NULL)
		return (NULL);

	pa = VM_PAGE_TO_PHYS(m);
	if (dcache_color_ignore == 0 && m->md.color != DCACHE_COLOR(pa)) {
		KASSERT(m->md.colors[0] == 0 && m->md.colors[1] == 0,
		    ("uma_small_alloc: free page %p still has mappings!", m));
		PMAP_STATS_INC(uma_nsmall_alloc_oc);
		m->md.color = DCACHE_COLOR(pa);
		dcache_page_inval(pa);
	}
	va = (void *)TLB_PHYS_TO_DIRECT(pa);
	if ((wait & M_ZERO) && (m->flags & PG_ZERO) == 0)
		cpu_block_zero(va, PAGE_SIZE);
	return (va);
}