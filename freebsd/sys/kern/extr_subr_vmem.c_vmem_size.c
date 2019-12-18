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
struct TYPE_5__ {int vm_inuse; int vm_size; int vm_quantum_shift; int /*<<< orphan*/ * vm_freelist; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int vmem_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ORDER2SIZE (int) ; 
#define  VMEM_ALLOC 130 
#define  VMEM_FREE 129 
 int /*<<< orphan*/  VMEM_LOCK (TYPE_1__*) ; 
#define  VMEM_MAXFREE 128 
 int /*<<< orphan*/  VMEM_MAXORDER ; 
 int /*<<< orphan*/  VMEM_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

vmem_size_t
vmem_size(vmem_t *vm, int typemask)
{
	int i;

	switch (typemask) {
	case VMEM_ALLOC:
		return vm->vm_inuse;
	case VMEM_FREE:
		return vm->vm_size - vm->vm_inuse;
	case VMEM_FREE|VMEM_ALLOC:
		return vm->vm_size;
	case VMEM_MAXFREE:
		VMEM_LOCK(vm);
		for (i = VMEM_MAXORDER - 1; i >= 0; i--) {
			if (LIST_EMPTY(&vm->vm_freelist[i]))
				continue;
			VMEM_UNLOCK(vm);
			return ((vmem_size_t)ORDER2SIZE(i) <<
			    vm->vm_quantum_shift);
		}
		VMEM_UNLOCK(vm);
		return (0);
	default:
		panic("vmem_size");
	}
}