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
typedef  int /*<<< orphan*/  u32 ;
struct pcpu {struct lowcore* lowcore; } ;
struct lowcore {unsigned long nodat_stack; unsigned long async_stack; int cpu_nr; int br_r1_trampoline; scalar_t__ spinlock_index; int /*<<< orphan*/  spinlock_lockval; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  LC_ORDER ; 
 int /*<<< orphan*/  S390_lowcore ; 
 int /*<<< orphan*/  SIGP_SET_PREFIX ; 
 unsigned long STACK_INIT_OFFSET ; 
 int /*<<< orphan*/  THREAD_SIZE_ORDER ; 
 unsigned long __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_spin_lockval (int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 struct lowcore** lowcore_ptr ; 
 int /*<<< orphan*/  memcpy (struct lowcore*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nmi_alloc_per_cpu (struct lowcore*) ; 
 int /*<<< orphan*/  nmi_free_per_cpu (struct lowcore*) ; 
 struct pcpu* pcpu_devices ; 
 int /*<<< orphan*/  pcpu_sigp_retry (struct pcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long stack_alloc () ; 
 int /*<<< orphan*/  stack_free (unsigned long) ; 
 scalar_t__ vdso_alloc_per_cpu (struct lowcore*) ; 

__attribute__((used)) static int pcpu_alloc_lowcore(struct pcpu *pcpu, int cpu)
{
	unsigned long async_stack, nodat_stack;
	struct lowcore *lc;

	if (pcpu != &pcpu_devices[0]) {
		pcpu->lowcore =	(struct lowcore *)
			__get_free_pages(GFP_KERNEL | GFP_DMA, LC_ORDER);
		nodat_stack = __get_free_pages(GFP_KERNEL, THREAD_SIZE_ORDER);
		if (!pcpu->lowcore || !nodat_stack)
			goto out;
	} else {
		nodat_stack = pcpu->lowcore->nodat_stack - STACK_INIT_OFFSET;
	}
	async_stack = stack_alloc();
	if (!async_stack)
		goto out;
	lc = pcpu->lowcore;
	memcpy(lc, &S390_lowcore, 512);
	memset((char *) lc + 512, 0, sizeof(*lc) - 512);
	lc->async_stack = async_stack + STACK_INIT_OFFSET;
	lc->nodat_stack = nodat_stack + STACK_INIT_OFFSET;
	lc->cpu_nr = cpu;
	lc->spinlock_lockval = arch_spin_lockval(cpu);
	lc->spinlock_index = 0;
	lc->br_r1_trampoline = 0x07f1;	/* br %r1 */
	if (nmi_alloc_per_cpu(lc))
		goto out_async;
	if (vdso_alloc_per_cpu(lc))
		goto out_mcesa;
	lowcore_ptr[cpu] = lc;
	pcpu_sigp_retry(pcpu, SIGP_SET_PREFIX, (u32)(unsigned long) lc);
	return 0;

out_mcesa:
	nmi_free_per_cpu(lc);
out_async:
	stack_free(async_stack);
out:
	if (pcpu != &pcpu_devices[0]) {
		free_pages(nodat_stack, THREAD_SIZE_ORDER);
		free_pages((unsigned long) pcpu->lowcore, LC_ORDER);
	}
	return -ENOMEM;
}