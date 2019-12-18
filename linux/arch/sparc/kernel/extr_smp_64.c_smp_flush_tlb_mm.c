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
struct mm_struct {int /*<<< orphan*/  mm_users; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_HWBITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECONDARY_CONTEXT ; 
 int /*<<< orphan*/  __flush_tlb_mm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_cross_call_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcall_flush_tlb_mm ; 

void smp_flush_tlb_mm(struct mm_struct *mm)
{
	u32 ctx = CTX_HWBITS(mm->context);
	int cpu = get_cpu();

	if (atomic_read(&mm->mm_users) == 1) {
		cpumask_copy(mm_cpumask(mm), cpumask_of(cpu));
		goto local_flush_and_out;
	}

	smp_cross_call_masked(&xcall_flush_tlb_mm,
			      ctx, 0, 0,
			      mm_cpumask(mm));

local_flush_and_out:
	__flush_tlb_mm(ctx, SECONDARY_CONTEXT);

	put_cpu();
}