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
typedef  size_t vm_size_t ;
typedef  size_t vm_offset_t ;
struct thread {TYPE_2__* td_proc; } ;
struct TYPE_4__ {TYPE_1__* p_vmspace; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
#define  KERN_PROTECTION_FAILURE 130 
#define  KERN_RESOURCE_SHORTAGE 129 
#define  KERN_SUCCESS 128 
 size_t PAGE_MASK ; 
 int PROT_EXTRACT (int) ; 
 int PROT_MAX (int) ; 
 int PROT_MAX_EXTRACT (int) ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int _PROT_ALL ; 
 scalar_t__ round_page (size_t) ; 
 int vm_map_protect (int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ ) ; 

int
kern_mprotect(struct thread *td, uintptr_t addr0, size_t size, int prot)
{
	vm_offset_t addr;
	vm_size_t pageoff;
	int vm_error, max_prot;

	addr = addr0;
	if ((prot & ~(_PROT_ALL | PROT_MAX(_PROT_ALL))) != 0)
		return (EINVAL);
	max_prot = PROT_MAX_EXTRACT(prot);
	prot = PROT_EXTRACT(prot);
	pageoff = (addr & PAGE_MASK);
	addr -= pageoff;
	size += pageoff;
	size = (vm_size_t) round_page(size);
#ifdef COMPAT_FREEBSD32
	if (SV_PROC_FLAG(td->td_proc, SV_ILP32)) {
		if (((addr + size) & 0xffffffff) < addr)
			return (EINVAL);
	} else
#endif
	if (addr + size < addr)
		return (EINVAL);

	vm_error = KERN_SUCCESS;
	if (max_prot != 0) {
		if ((max_prot & prot) != prot)
			return (EINVAL);
		vm_error = vm_map_protect(&td->td_proc->p_vmspace->vm_map,
		    addr, addr + size, max_prot, TRUE);
	}
	if (vm_error == KERN_SUCCESS)
		vm_error = vm_map_protect(&td->td_proc->p_vmspace->vm_map,
		    addr, addr + size, prot, FALSE);

	switch (vm_error) {
	case KERN_SUCCESS:
		return (0);
	case KERN_PROTECTION_FAILURE:
		return (EACCES);
	case KERN_RESOURCE_SHORTAGE:
		return (ENOMEM);
	}
	return (EINVAL);
}