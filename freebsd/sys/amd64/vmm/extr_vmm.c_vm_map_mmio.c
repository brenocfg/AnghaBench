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
struct vm {int /*<<< orphan*/  vmspace; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * vmm_mmio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

int
vm_map_mmio(struct vm *vm, vm_paddr_t gpa, size_t len, vm_paddr_t hpa)
{
	vm_object_t obj;

	if ((obj = vmm_mmio_alloc(vm->vmspace, gpa, len, hpa)) == NULL)
		return (ENOMEM);
	else
		return (0);
}