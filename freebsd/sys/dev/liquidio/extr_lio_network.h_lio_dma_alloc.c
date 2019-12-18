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
typedef  int /*<<< orphan*/  vm_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 scalar_t__ kmem_alloc_contig (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t lio_get_order (size_t) ; 
 int /*<<< orphan*/  vtophys (void*) ; 

__attribute__((used)) static inline void *
lio_dma_alloc(size_t size, vm_paddr_t *dma_handle)
{
	size_t	align;
	void	*mem;

	align = PAGE_SIZE << lio_get_order(size);
	mem = (void *)kmem_alloc_contig(size, M_WAITOK, 0, ~0ul, align, 0,
	    VM_MEMATTR_DEFAULT);
	if (mem != NULL)
		*dma_handle = vtophys(mem);
	else
		*dma_handle = 0;

	return (mem);
}