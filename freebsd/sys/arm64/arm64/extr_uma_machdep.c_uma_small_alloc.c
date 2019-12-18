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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int M_NODUMP ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_ZERO ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMA_SLAB_PRIV ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_add_page (int /*<<< orphan*/ ) ; 
 int malloc2vm_flags (int) ; 
 TYPE_1__* vm_page_alloc_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void *
uma_small_alloc(uma_zone_t zone, vm_size_t bytes, int domain, u_int8_t *flags,
    int wait)
{
	vm_page_t m;
	vm_paddr_t pa;
	void *va;

	*flags = UMA_SLAB_PRIV;
	m = vm_page_alloc_domain(NULL, 0, domain,
	    malloc2vm_flags(wait) | VM_ALLOC_NOOBJ | VM_ALLOC_WIRED);
	if (m == NULL)
		return (NULL);
	pa = m->phys_addr;
	if ((wait & M_NODUMP) == 0)
		dump_add_page(pa);
	va = (void *)PHYS_TO_DMAP(pa);
	if ((wait & M_ZERO) && (m->flags & PG_ZERO) == 0)
		bzero(va, PAGE_SIZE);
	return (va);
}