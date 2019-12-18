#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* uma_slab_t ;
struct domainset {int dummy; } ;
struct TYPE_5__ {int us_flags; int /*<<< orphan*/  us_domain; int /*<<< orphan*/  us_size; void* us_data; } ;

/* Variables and functions */
 struct domainset* DOMAINSET_FIXED (int) ; 
 struct domainset* DOMAINSET_RR () ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKIP_NONE ; 
 int UMA_ANYDOMAIN ; 
 int UMA_SLAB_KERNEL ; 
 int UMA_SLAB_MALLOC ; 
 scalar_t__ VM_DOMAIN_EMPTY (int) ; 
 scalar_t__ kmem_malloc_domainset (struct domainset*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 int /*<<< orphan*/  slabzone ; 
 int /*<<< orphan*/  uma_total_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_phys_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsetslab (scalar_t__,TYPE_1__*) ; 
 TYPE_1__* zone_alloc_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zone_free_item (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *
uma_large_malloc_domain(vm_size_t size, int domain, int wait)
{
	struct domainset *policy;
	vm_offset_t addr;
	uma_slab_t slab;

	if (domain != UMA_ANYDOMAIN) {
		/* avoid allocs targeting empty domains */
		if (VM_DOMAIN_EMPTY(domain))
			domain = UMA_ANYDOMAIN;
	}
	slab = zone_alloc_item(slabzone, NULL, domain, wait);
	if (slab == NULL)
		return (NULL);
	policy = (domain == UMA_ANYDOMAIN) ? DOMAINSET_RR() :
	    DOMAINSET_FIXED(domain);
	addr = kmem_malloc_domainset(policy, size, wait);
	if (addr != 0) {
		vsetslab(addr, slab);
		slab->us_data = (void *)addr;
		slab->us_flags = UMA_SLAB_KERNEL | UMA_SLAB_MALLOC;
		slab->us_size = size;
		slab->us_domain = vm_phys_domain(PHYS_TO_VM_PAGE(
		    pmap_kextract(addr)));
		uma_total_inc(size);
	} else {
		zone_free_item(slabzone, slab, NULL, SKIP_NONE);
	}

	return ((void *)addr);
}