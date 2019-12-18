#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_ooffset_t ;
struct vm {TYPE_1__* vmspace; struct mem_map* mem_maps; struct mem_seg* mem_segs; } ;
struct mem_seg {scalar_t__ len; int /*<<< orphan*/ * object; } ;
struct mem_map {scalar_t__ len; int segid; int prot; int flags; scalar_t__ segoff; scalar_t__ gpa; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 scalar_t__ PAGE_MASK ; 
 int /*<<< orphan*/  VMFS_NO_SPACE ; 
 int VM_MAP_WIRE_NOHOLES ; 
 int VM_MAP_WIRE_USER ; 
 int VM_MAX_MEMMAPS ; 
 int VM_MAX_MEMSEGS ; 
 int VM_MEMMAP_F_WIRED ; 
 int VM_PROT_ALL ; 
 int vm_map_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_remove (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int vm_map_wire (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_object_reference (int /*<<< orphan*/ *) ; 

int
vm_mmap_memseg(struct vm *vm, vm_paddr_t gpa, int segid, vm_ooffset_t first,
    size_t len, int prot, int flags)
{
	struct mem_seg *seg;
	struct mem_map *m, *map;
	vm_ooffset_t last;
	int i, error;

	if (prot == 0 || (prot & ~(VM_PROT_ALL)) != 0)
		return (EINVAL);

	if (flags & ~VM_MEMMAP_F_WIRED)
		return (EINVAL);

	if (segid < 0 || segid >= VM_MAX_MEMSEGS)
		return (EINVAL);

	seg = &vm->mem_segs[segid];
	if (seg->object == NULL)
		return (EINVAL);

	last = first + len;
	if (first < 0 || first >= last || last > seg->len)
		return (EINVAL);

	if ((gpa | first | last) & PAGE_MASK)
		return (EINVAL);

	map = NULL;
	for (i = 0; i < VM_MAX_MEMMAPS; i++) {
		m = &vm->mem_maps[i];
		if (m->len == 0) {
			map = m;
			break;
		}
	}

	if (map == NULL)
		return (ENOSPC);

	error = vm_map_find(&vm->vmspace->vm_map, seg->object, first, &gpa,
	    len, 0, VMFS_NO_SPACE, prot, prot, 0);
	if (error != KERN_SUCCESS)
		return (EFAULT);

	vm_object_reference(seg->object);

	if (flags & VM_MEMMAP_F_WIRED) {
		error = vm_map_wire(&vm->vmspace->vm_map, gpa, gpa + len,
		    VM_MAP_WIRE_USER | VM_MAP_WIRE_NOHOLES);
		if (error != KERN_SUCCESS) {
			vm_map_remove(&vm->vmspace->vm_map, gpa, gpa + len);
			return (error == KERN_RESOURCE_SHORTAGE ? ENOMEM :
			    EFAULT);
		}
	}

	map->gpa = gpa;
	map->len = len;
	map->segoff = first;
	map->segid = segid;
	map->prot = prot;
	map->flags = flags;
	return (0);
}