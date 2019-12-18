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
typedef  scalar_t__ vm_paddr_t ;
struct vm {void* iommu; struct mem_map* mem_maps; } ;
struct mem_map {int flags; scalar_t__ gpa; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ DMAP_TO_PHYS (uintptr_t) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_SIZE ; 
 int VM_MAX_MEMMAPS ; 
 int VM_MEMMAP_F_IOMMU ; 
 int VM_MEMMAP_F_WIRED ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int /*<<< orphan*/  iommu_create_mapping (void*,scalar_t__,scalar_t__,int) ; 
 void* iommu_host_domain () ; 
 int /*<<< orphan*/  iommu_invalidate_tlb (void*) ; 
 int /*<<< orphan*/  iommu_remove_mapping (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  sysmem_mapping (struct vm*,struct mem_map*) ; 
 void* vm_gpa_hold (struct vm*,int,scalar_t__,int,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  vm_gpa_release (void*) ; 
 int /*<<< orphan*/  vm_name (struct vm*) ; 

__attribute__((used)) static void
vm_iommu_modify(struct vm *vm, bool map)
{
	int i, sz;
	vm_paddr_t gpa, hpa;
	struct mem_map *mm;
	void *vp, *cookie, *host_domain;

	sz = PAGE_SIZE;
	host_domain = iommu_host_domain();

	for (i = 0; i < VM_MAX_MEMMAPS; i++) {
		mm = &vm->mem_maps[i];
		if (!sysmem_mapping(vm, mm))
			continue;

		if (map) {
			KASSERT((mm->flags & VM_MEMMAP_F_IOMMU) == 0,
			    ("iommu map found invalid memmap %#lx/%#lx/%#x",
			    mm->gpa, mm->len, mm->flags));
			if ((mm->flags & VM_MEMMAP_F_WIRED) == 0)
				continue;
			mm->flags |= VM_MEMMAP_F_IOMMU;
		} else {
			if ((mm->flags & VM_MEMMAP_F_IOMMU) == 0)
				continue;
			mm->flags &= ~VM_MEMMAP_F_IOMMU;
			KASSERT((mm->flags & VM_MEMMAP_F_WIRED) != 0,
			    ("iommu unmap found invalid memmap %#lx/%#lx/%#x",
			    mm->gpa, mm->len, mm->flags));
		}

		gpa = mm->gpa;
		while (gpa < mm->gpa + mm->len) {
			vp = vm_gpa_hold(vm, -1, gpa, PAGE_SIZE, VM_PROT_WRITE,
					 &cookie);
			KASSERT(vp != NULL, ("vm(%s) could not map gpa %#lx",
			    vm_name(vm), gpa));

			vm_gpa_release(cookie);

			hpa = DMAP_TO_PHYS((uintptr_t)vp);
			if (map) {
				iommu_create_mapping(vm->iommu, gpa, hpa, sz);
				iommu_remove_mapping(host_domain, hpa, sz);
			} else {
				iommu_remove_mapping(vm->iommu, gpa, sz);
				iommu_create_mapping(host_domain, hpa, hpa, sz);
			}

			gpa += PAGE_SIZE;
		}
	}

	/*
	 * Invalidate the cached translations associated with the domain
	 * from which pages were removed.
	 */
	if (map)
		iommu_invalidate_tlb(host_domain);
	else
		iommu_invalidate_tlb(vm->iommu);
}