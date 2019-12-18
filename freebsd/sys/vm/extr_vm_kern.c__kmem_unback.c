#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ vm_object_t ;
struct vmem {int dummy; } ;
struct TYPE_10__ {struct vmem* vmd_kernel_arena; struct vmem* vmd_kernel_rwx_arena; } ;
struct TYPE_9__ {int oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (scalar_t__) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (scalar_t__) ; 
 int VPO_KMEM_EXEC ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  atop (scalar_t__) ; 
 scalar_t__ kernel_object ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_8__* vm_dom ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 TYPE_1__* vm_page_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_page_next (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (TYPE_1__*) ; 
 int vm_phys_domain (TYPE_1__*) ; 

__attribute__((used)) static struct vmem *
_kmem_unback(vm_object_t object, vm_offset_t addr, vm_size_t size)
{
	struct vmem *arena;
	vm_page_t m, next;
	vm_offset_t end, offset;
	int domain;

	KASSERT(object == kernel_object,
	    ("kmem_unback: only supports kernel object."));

	if (size == 0)
		return (NULL);
	pmap_remove(kernel_pmap, addr, addr + size);
	offset = addr - VM_MIN_KERNEL_ADDRESS;
	end = offset + size;
	VM_OBJECT_WLOCK(object);
	m = vm_page_lookup(object, atop(offset)); 
	domain = vm_phys_domain(m);
#if VM_NRESERVLEVEL > 0
	if (__predict_true((m->oflags & VPO_KMEM_EXEC) == 0))
		arena = vm_dom[domain].vmd_kernel_arena;
	else
		arena = vm_dom[domain].vmd_kernel_rwx_arena;
#else
	arena = vm_dom[domain].vmd_kernel_arena;
#endif
	for (; offset < end; offset += PAGE_SIZE, m = next) {
		next = vm_page_next(m);
		vm_page_unwire_noq(m);
		vm_page_free(m);
	}
	VM_OBJECT_WUNLOCK(object);

	return (arena);
}