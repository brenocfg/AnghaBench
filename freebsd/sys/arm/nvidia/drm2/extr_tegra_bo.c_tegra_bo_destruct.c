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
struct tegra_bo {scalar_t__ vbase; int npages; int /*<<< orphan*/ * cdev_pager; TYPE_2__** m; TYPE_1__ gem_obj; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_FICTITIOUS ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_pager_free_page (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_arena ; 
 int /*<<< orphan*/  pmap_qremove (scalar_t__,int) ; 
 size_t round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (TYPE_2__*) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,scalar_t__,size_t) ; 

__attribute__((used)) static void
tegra_bo_destruct(struct tegra_bo *bo)
{
	vm_page_t m;
	size_t size;
	int i;

	if (bo->cdev_pager == NULL)
		return;

	size = round_page(bo->gem_obj.size);
	if (bo->vbase != 0)
		pmap_qremove(bo->vbase, bo->npages);

	VM_OBJECT_WLOCK(bo->cdev_pager);
	for (i = 0; i < bo->npages; i++) {
		m = bo->m[i];
		cdev_pager_free_page(bo->cdev_pager, m);
		m->flags &= ~PG_FICTITIOUS;
		vm_page_unwire_noq(m);
		vm_page_free(m);
	}
	VM_OBJECT_WUNLOCK(bo->cdev_pager);

	vm_object_deallocate(bo->cdev_pager);
	if (bo->vbase != 0)
		vmem_free(kmem_arena, bo->vbase, size);
}