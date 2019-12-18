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
struct mm_struct {int /*<<< orphan*/  mm_users; int /*<<< orphan*/  context; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long CTX_HWBITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __flush_tlb_page (unsigned long,unsigned long) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 TYPE_1__* current ; 
 int get_cpu () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_cross_call_masked (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcall_flush_tlb_page ; 

void smp_flush_tlb_page(struct mm_struct *mm, unsigned long vaddr)
{
	unsigned long context = CTX_HWBITS(mm->context);
	int cpu = get_cpu();

	if (mm == current->mm && atomic_read(&mm->mm_users) == 1)
		cpumask_copy(mm_cpumask(mm), cpumask_of(cpu));
	else
		smp_cross_call_masked(&xcall_flush_tlb_page,
				      context, vaddr, 0,
				      mm_cpumask(mm));
	__flush_tlb_page(context, vaddr);

	put_cpu();
}