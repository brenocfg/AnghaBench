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
typedef  int /*<<< orphan*/ * vm_object_t ;
struct vmspace {int /*<<< orphan*/  vm_map; } ;
struct sglist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OBJT_SG ; 
 int /*<<< orphan*/  VMFS_NO_SPACE ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_PROT_RW ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 struct sglist* sglist_alloc (int,int /*<<< orphan*/ ) ; 
 int sglist_append_phys (struct sglist*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sglist_free (struct sglist*) ; 
 int vm_map_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 
 int vm_object_set_memattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_pager_allocate (int /*<<< orphan*/ ,struct sglist*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

vm_object_t
vmm_mmio_alloc(struct vmspace *vmspace, vm_paddr_t gpa, size_t len,
	       vm_paddr_t hpa)
{
	int error;
	vm_object_t obj;
	struct sglist *sg;

	sg = sglist_alloc(1, M_WAITOK);
	error = sglist_append_phys(sg, hpa, len);
	KASSERT(error == 0, ("error %d appending physaddr to sglist", error));

	obj = vm_pager_allocate(OBJT_SG, sg, len, VM_PROT_RW, 0, NULL);
	if (obj != NULL) {
		/*
		 * VT-x ignores the MTRR settings when figuring out the
		 * memory type for translations obtained through EPT.
		 *
		 * Therefore we explicitly force the pages provided by
		 * this object to be mapped as uncacheable.
		 */
		VM_OBJECT_WLOCK(obj);
		error = vm_object_set_memattr(obj, VM_MEMATTR_UNCACHEABLE);
		VM_OBJECT_WUNLOCK(obj);
		if (error != KERN_SUCCESS) {
			panic("vmm_mmio_alloc: vm_object_set_memattr error %d",
				error);
		}
		error = vm_map_find(&vmspace->vm_map, obj, 0, &gpa, len, 0,
				    VMFS_NO_SPACE, VM_PROT_RW, VM_PROT_RW, 0);
		if (error != KERN_SUCCESS) {
			vm_object_deallocate(obj);
			obj = NULL;
		}
	}

	/*
	 * Drop the reference on the sglist.
	 *
	 * If the scatter/gather object was successfully allocated then it
	 * has incremented the reference count on the sglist. Dropping the
	 * initial reference count ensures that the sglist will be freed
	 * when the object is deallocated.
	 * 
	 * If the object could not be allocated then we end up freeing the
	 * sglist.
	 */
	sglist_free(sg);

	return (obj);
}