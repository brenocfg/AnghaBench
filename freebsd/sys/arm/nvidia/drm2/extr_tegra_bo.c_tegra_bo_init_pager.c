#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct tegra_bo {int npages; TYPE_2__** m; int /*<<< orphan*/  vbase; int /*<<< orphan*/  cdev_pager; int /*<<< orphan*/  pbase; TYPE_1__ gem_obj; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  oflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int M_BESTFIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  PG_FICTITIOUS ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  VPO_UNMANAGED ; 
 int /*<<< orphan*/  kmem_arena ; 
 int /*<<< orphan*/  pmap_qenter (int /*<<< orphan*/ ,TYPE_2__**,int) ; 
 size_t round_page (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_insert (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vmem_alloc (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tegra_bo_init_pager(struct tegra_bo *bo)
{
	vm_page_t m;
	size_t size;
	int i;

	size = round_page(bo->gem_obj.size);

	bo->pbase = VM_PAGE_TO_PHYS(bo->m[0]);
	if (vmem_alloc(kmem_arena, size, M_WAITOK | M_BESTFIT, &bo->vbase))
		return (ENOMEM);

	VM_OBJECT_WLOCK(bo->cdev_pager);
	for (i = 0; i < bo->npages; i++) {
		m = bo->m[i];
		/*
		 * XXX This is a temporary hack.
		 * We need pager suitable for paging (mmap) managed
		 * real (non-fictitious) pages.
		 * - managed pages are needed for clean module unload.
		 * - aliasing fictitious page to real one is bad,
		 *   pmap cannot handle this situation without issues
		 *   It expects that
		 *    paddr = PHYS_TO_VM_PAGE(VM_PAGE_TO_PHYS(paddr))
		 *   for every single page passed to pmap.
		 */
		m->oflags &= ~VPO_UNMANAGED;
		m->flags |= PG_FICTITIOUS;
		if (vm_page_insert(m, bo->cdev_pager, i) != 0)
			return (EINVAL);
	}
	VM_OBJECT_WUNLOCK(bo->cdev_pager);

	pmap_qenter(bo->vbase, bo->m, bo->npages);
	return (0);
}