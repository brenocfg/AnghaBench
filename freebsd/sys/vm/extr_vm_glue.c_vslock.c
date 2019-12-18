#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
struct TYPE_6__ {TYPE_1__* p_vmspace; } ;
struct TYPE_5__ {size_t td_vslock_sz; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int KERN_SUCCESS ; 
 int VM_MAP_WIRE_NOHOLES ; 
 int VM_MAP_WIRE_SYSTEM ; 
 scalar_t__ atop (scalar_t__) ; 
 TYPE_3__* curproc ; 
 TYPE_2__* curthread ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int vm_map_wire (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 scalar_t__ vm_page_max_user_wired ; 

int
vslock(void *addr, size_t len)
{
	vm_offset_t end, last, start;
	vm_size_t npages;
	int error;

	last = (vm_offset_t)addr + len;
	start = trunc_page((vm_offset_t)addr);
	end = round_page(last);
	if (last < (vm_offset_t)addr || end < (vm_offset_t)addr)
		return (EINVAL);
	npages = atop(end - start);
	if (npages > vm_page_max_user_wired)
		return (ENOMEM);
	error = vm_map_wire(&curproc->p_vmspace->vm_map, start, end,
	    VM_MAP_WIRE_SYSTEM | VM_MAP_WIRE_NOHOLES);
	if (error == KERN_SUCCESS) {
		curthread->td_vslock_sz += len;
		return (0);
	}

	/*
	 * Return EFAULT on error to match copy{in,out}() behaviour
	 * rather than returning ENOMEM like mlock() would.
	 */
	return (EFAULT);
}