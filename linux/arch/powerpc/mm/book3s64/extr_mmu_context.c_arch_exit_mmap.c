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
struct TYPE_3__ {size_t id; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_4__ {scalar_t__ prtb0; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_pagetable_cache (struct mm_struct*) ; 
 TYPE_2__* process_tb ; 
 scalar_t__ radix_enabled () ; 

void arch_exit_mmap(struct mm_struct *mm)
{
	destroy_pagetable_cache(mm);

	if (radix_enabled()) {
		/*
		 * Radix doesn't have a valid bit in the process table
		 * entries. However we know that at least P9 implementation
		 * will avoid caching an entry with an invalid RTS field,
		 * and 0 is invalid. So this will do.
		 *
		 * This runs before the "fullmm" tlb flush in exit_mmap,
		 * which does a RIC=2 tlbie to clear the process table
		 * entry. See the "fullmm" comments in tlb-radix.c.
		 *
		 * No barrier required here after the store because
		 * this process will do the invalidate, which starts with
		 * ptesync.
		 */
		process_tb[mm->context.id].prtb0 = 0;
	}
}