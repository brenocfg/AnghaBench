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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  unsigned int const uintmax_t ;
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ sf_sp; } ;
struct pcb {TYPE_1__ pcb_regs; } ;
struct TYPE_4__ {scalar_t__ td_kstack; struct pcb* td_pcb; } ;

/* Variables and functions */
 scalar_t__ ARM_RAS_END ; 
 scalar_t__ ARM_RAS_START ; 
 int /*<<< orphan*/  ARM_TP_ADDRESS ; 
 scalar_t__ USPACE_SVC_STACK_TOP ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 scalar_t__ arm32_ptob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_lock_cache_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_physmem_print_tables () ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bufinit () ; 
 int /*<<< orphan*/  devmap_print_table () ; 
 int /*<<< orphan*/  identify_arm_cpu () ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  kmi ; 
 int /*<<< orphan*/  pmap_kenter_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_postinit () ; 
 int /*<<< orphan*/  pmap_set_pcb_pagedir (int /*<<< orphan*/ ,struct pcb*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int const,unsigned int const) ; 
 int /*<<< orphan*/  realmem ; 
 TYPE_2__ thread0 ; 
 int /*<<< orphan*/  vector_page_setprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_free_count () ; 
 int /*<<< orphan*/  vm_ksubmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_pager_bufferinit () ; 

__attribute__((used)) static void
cpu_startup(void *dummy)
{
	struct pcb *pcb = thread0.td_pcb;
	const unsigned int mbyte = 1024 * 1024;
#if __ARM_ARCH < 6 && !defined(ARM_CACHE_LOCK_ENABLE)
	vm_page_t m;
#endif

	identify_arm_cpu();

	vm_ksubmap_init(&kmi);

	/*
	 * Display the RAM layout.
	 */
	printf("real memory  = %ju (%ju MB)\n",
	    (uintmax_t)arm32_ptob(realmem),
	    (uintmax_t)arm32_ptob(realmem) / mbyte);
	printf("avail memory = %ju (%ju MB)\n",
	    (uintmax_t)arm32_ptob(vm_free_count()),
	    (uintmax_t)arm32_ptob(vm_free_count()) / mbyte);
	if (bootverbose) {
		arm_physmem_print_tables();
		devmap_print_table();
	}

	bufinit();
	vm_pager_bufferinit();
	pcb->pcb_regs.sf_sp = (u_int)thread0.td_kstack +
	    USPACE_SVC_STACK_TOP;
	pmap_set_pcb_pagedir(kernel_pmap, pcb);
#if __ARM_ARCH < 6
	vector_page_setprot(VM_PROT_READ);
	pmap_postinit();
#ifdef ARM_CACHE_LOCK_ENABLE
	pmap_kenter_user(ARM_TP_ADDRESS, ARM_TP_ADDRESS);
	arm_lock_cache_line(ARM_TP_ADDRESS);
#else
	m = vm_page_alloc(NULL, 0, VM_ALLOC_NOOBJ | VM_ALLOC_ZERO);
	pmap_kenter_user(ARM_TP_ADDRESS, VM_PAGE_TO_PHYS(m));
#endif
	*(uint32_t *)ARM_RAS_START = 0;
	*(uint32_t *)ARM_RAS_END = 0xffffffff;
#endif
}