#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_info {scalar_t__ slb_preload_nr; } ;
struct mm_struct {unsigned long mmap_base; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 scalar_t__ SLB_PRELOAD_NR ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  is_kernel_addr (unsigned long) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ preload_add (struct thread_info*,unsigned long) ; 
 int /*<<< orphan*/  slb_allocate_user (struct mm_struct*,unsigned long) ; 

void slb_setup_new_exec(void)
{
	struct thread_info *ti = current_thread_info();
	struct mm_struct *mm = current->mm;
	unsigned long exec = 0x10000000;

	WARN_ON(irqs_disabled());

	/*
	 * preload cache can only be used to determine whether a SLB
	 * entry exists if it does not start to overflow.
	 */
	if (ti->slb_preload_nr + 2 > SLB_PRELOAD_NR)
		return;

	hard_irq_disable();

	/*
	 * We have no good place to clear the slb preload cache on exec,
	 * flush_thread is about the earliest arch hook but that happens
	 * after we switch to the mm and have aleady preloaded the SLBEs.
	 *
	 * For the most part that's probably okay to use entries from the
	 * previous exec, they will age out if unused. It may turn out to
	 * be an advantage to clear the cache before switching to it,
	 * however.
	 */

	/*
	 * preload some userspace segments into the SLB.
	 * Almost all 32 and 64bit PowerPC executables are linked at
	 * 0x10000000 so it makes sense to preload this segment.
	 */
	if (!is_kernel_addr(exec)) {
		if (preload_add(ti, exec))
			slb_allocate_user(mm, exec);
	}

	/* Libraries and mmaps. */
	if (!is_kernel_addr(mm->mmap_base)) {
		if (preload_add(ti, mm->mmap_base))
			slb_allocate_user(mm, mm->mmap_base);
	}

	/* see switch_slb */
	asm volatile("isync" : : : "memory");

	local_irq_enable();
}