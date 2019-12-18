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
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_FICTITIOUS ; 
 int TTM_PAGE_FLAG_DMA32 ; 
 int TTM_PAGE_FLAG_ZERO_ALLOC ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VPO_UNMANAGED ; 
 int /*<<< orphan*/  ttm_caching_state_to_vm (int) ; 
 TYPE_1__* ttm_vm_page_alloc_any (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ttm_vm_page_alloc_dma32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_page_t
ttm_vm_page_alloc(int flags, enum ttm_caching_state cstate)
{
	vm_page_t p;
	vm_memattr_t memattr;
	int req;

	memattr = ttm_caching_state_to_vm(cstate);
	req = VM_ALLOC_NORMAL | VM_ALLOC_WIRED | VM_ALLOC_NOOBJ;
	if ((flags & TTM_PAGE_FLAG_ZERO_ALLOC) != 0)
		req |= VM_ALLOC_ZERO;

	if ((flags & TTM_PAGE_FLAG_DMA32) != 0)
		p = ttm_vm_page_alloc_dma32(req, memattr);
	else
		p = ttm_vm_page_alloc_any(req, memattr);

	if (p != NULL) {
		p->oflags &= ~VPO_UNMANAGED;
		p->flags |= PG_FICTITIOUS;
	}
	return (p);
}