#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcb {int /*<<< orphan*/  pcb_regs; } ;
struct TYPE_3__ {int td_kstack; int td_kstack_pages; struct pcb* td_pcb; int /*<<< orphan*/ * td_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCPU_SIZE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KSTACK_PAGES ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,struct pcb*) ; 
 int /*<<< orphan*/  curpcb ; 
 int /*<<< orphan*/  dpcpu_init (void*,int /*<<< orphan*/ ) ; 
 int kstack0 ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ platform_processor_id () ; 
 scalar_t__ pmap_steal_memory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc0 ; 
 int /*<<< orphan*/  proc_linkup0 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ thread0 ; 

void
mips_proc0_init(void)
{
#ifdef SMP
	if (platform_processor_id() != 0)
		panic("BSP must be processor number 0");
#endif
	proc_linkup0(&proc0, &thread0);

	KASSERT((kstack0 & PAGE_MASK) == 0,
		("kstack0 is not aligned on a page boundary: 0x%0lx",
		(long)kstack0));
	thread0.td_kstack = kstack0;
	thread0.td_kstack_pages = KSTACK_PAGES;
	/* 
	 * Do not use cpu_thread_alloc to initialize these fields 
	 * thread0 is the only thread that has kstack located in KSEG0 
	 * while cpu_thread_alloc handles kstack allocated in KSEG2.
	 */
	thread0.td_pcb = (struct pcb *)(thread0.td_kstack +
	    thread0.td_kstack_pages * PAGE_SIZE) - 1;
	thread0.td_frame = &thread0.td_pcb->pcb_regs;

	/* Steal memory for the dynamic per-cpu area. */
	dpcpu_init((void *)pmap_steal_memory(DPCPU_SIZE), 0);

	PCPU_SET(curpcb, thread0.td_pcb);
	/*
	 * There is no need to initialize md_upte array for thread0 as it's
	 * located in .bss section and should be explicitly zeroed during 
	 * kernel initialization.
	 */
}