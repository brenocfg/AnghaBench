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
struct mm_struct {unsigned long start_brk; } ;
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

void preload_new_slb_context(unsigned long start, unsigned long sp)
{
	struct thread_info *ti = current_thread_info();
	struct mm_struct *mm = current->mm;
	unsigned long heap = mm->start_brk;

	WARN_ON(irqs_disabled());

	/* see above */
	if (ti->slb_preload_nr + 3 > SLB_PRELOAD_NR)
		return;

	hard_irq_disable();

	/* Userspace entry address. */
	if (!is_kernel_addr(start)) {
		if (preload_add(ti, start))
			slb_allocate_user(mm, start);
	}

	/* Top of stack, grows down. */
	if (!is_kernel_addr(sp)) {
		if (preload_add(ti, sp))
			slb_allocate_user(mm, sp);
	}

	/* Bottom of heap, grows up. */
	if (heap && !is_kernel_addr(heap)) {
		if (preload_add(ti, heap))
			slb_allocate_user(mm, heap);
	}

	/* see switch_slb */
	asm volatile("isync" : : : "memory");

	local_irq_enable();
}