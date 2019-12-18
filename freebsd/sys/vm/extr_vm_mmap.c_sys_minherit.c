#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_inherit_t ;
struct thread {TYPE_2__* td_proc; } ;
struct minherit_args {int len; int /*<<< orphan*/  inherit; scalar_t__ addr; } ;
struct TYPE_4__ {TYPE_1__* p_vmspace; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
#define  KERN_PROTECTION_FAILURE 129 
#define  KERN_SUCCESS 128 
 int PAGE_MASK ; 
 scalar_t__ round_page (int) ; 
 int vm_map_inherit (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

int
sys_minherit(struct thread *td, struct minherit_args *uap)
{
	vm_offset_t addr;
	vm_size_t size, pageoff;
	vm_inherit_t inherit;

	addr = (vm_offset_t)uap->addr;
	size = uap->len;
	inherit = uap->inherit;

	pageoff = (addr & PAGE_MASK);
	addr -= pageoff;
	size += pageoff;
	size = (vm_size_t) round_page(size);
	if (addr + size < addr)
		return (EINVAL);

	switch (vm_map_inherit(&td->td_proc->p_vmspace->vm_map, addr,
	    addr + size, inherit)) {
	case KERN_SUCCESS:
		return (0);
	case KERN_PROTECTION_FAILURE:
		return (EACCES);
	}
	return (EINVAL);
}