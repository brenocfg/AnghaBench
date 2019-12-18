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
struct vmm_stat_type {int dummy; } ;
struct vm {int /*<<< orphan*/  vmspace; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VMM_MEM_RESIDENT ; 
 int /*<<< orphan*/  vmm_stat_set (struct vm*,int,int /*<<< orphan*/ ,int) ; 
 int vmspace_resident_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_get_rescnt(struct vm *vm, int vcpu, struct vmm_stat_type *stat)
{

	if (vcpu == 0) {
		vmm_stat_set(vm, vcpu, VMM_MEM_RESIDENT,
	       	    PAGE_SIZE * vmspace_resident_count(vm->vmspace));
	}	
}