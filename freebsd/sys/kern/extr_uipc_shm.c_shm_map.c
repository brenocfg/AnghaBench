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
typedef  size_t vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct shmfd {scalar_t__ shm_size; int /*<<< orphan*/  shm_kmappings; int /*<<< orphan*/  shm_object; } ;
struct file {scalar_t__ f_type; struct shmfd* f_data; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ DTYPE_SHM ; 
 int EINVAL ; 
 int KERN_SUCCESS ; 
 scalar_t__ PAGE_MASK ; 
 int /*<<< orphan*/  VMFS_OPTIMAL_SPACE ; 
 int VM_MAP_WIRE_NOHOLES ; 
 int VM_MAP_WIRE_SYSTEM ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ round_page (size_t) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int vm_map_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 size_t vm_map_min (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_remove (int /*<<< orphan*/ ,size_t,size_t) ; 
 int vm_map_wire (int /*<<< orphan*/ ,size_t,size_t,int) ; 
 int vm_mmap_to_errno (int) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_reference_locked (int /*<<< orphan*/ ) ; 

int
shm_map(struct file *fp, size_t size, off_t offset, void **memp)
{
	struct shmfd *shmfd;
	vm_offset_t kva, ofs;
	vm_object_t obj;
	int rv;

	if (fp->f_type != DTYPE_SHM)
		return (EINVAL);
	shmfd = fp->f_data;
	obj = shmfd->shm_object;
	VM_OBJECT_WLOCK(obj);
	/*
	 * XXXRW: This validation is probably insufficient, and subject to
	 * sign errors.  It should be fixed.
	 */
	if (offset >= shmfd->shm_size ||
	    offset + size > round_page(shmfd->shm_size)) {
		VM_OBJECT_WUNLOCK(obj);
		return (EINVAL);
	}

	shmfd->shm_kmappings++;
	vm_object_reference_locked(obj);
	VM_OBJECT_WUNLOCK(obj);

	/* Map the object into the kernel_map and wire it. */
	kva = vm_map_min(kernel_map);
	ofs = offset & PAGE_MASK;
	offset = trunc_page(offset);
	size = round_page(size + ofs);
	rv = vm_map_find(kernel_map, obj, offset, &kva, size, 0,
	    VMFS_OPTIMAL_SPACE, VM_PROT_READ | VM_PROT_WRITE,
	    VM_PROT_READ | VM_PROT_WRITE, 0);
	if (rv == KERN_SUCCESS) {
		rv = vm_map_wire(kernel_map, kva, kva + size,
		    VM_MAP_WIRE_SYSTEM | VM_MAP_WIRE_NOHOLES);
		if (rv == KERN_SUCCESS) {
			*memp = (void *)(kva + ofs);
			return (0);
		}
		vm_map_remove(kernel_map, kva, kva + size);
	} else
		vm_object_deallocate(obj);

	/* On failure, drop our mapping reference. */
	VM_OBJECT_WLOCK(obj);
	shmfd->shm_kmappings--;
	VM_OBJECT_WUNLOCK(obj);

	return (vm_mmap_to_errno(rv));
}