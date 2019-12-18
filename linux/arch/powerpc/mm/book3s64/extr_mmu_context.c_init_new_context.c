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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int id; int /*<<< orphan*/  copros; int /*<<< orphan*/  active_cpus; int /*<<< orphan*/ * pmd_frag; int /*<<< orphan*/ * pte_frag; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hash__init_new_context (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_iommu_init (struct mm_struct*) ; 
 int radix__init_new_context (struct mm_struct*) ; 
 scalar_t__ radix_enabled () ; 

int init_new_context(struct task_struct *tsk, struct mm_struct *mm)
{
	int index;

	if (radix_enabled())
		index = radix__init_new_context(mm);
	else
		index = hash__init_new_context(mm);

	if (index < 0)
		return index;

	mm->context.id = index;

	mm->context.pte_frag = NULL;
	mm->context.pmd_frag = NULL;
#ifdef CONFIG_SPAPR_TCE_IOMMU
	mm_iommu_init(mm);
#endif
	atomic_set(&mm->context.active_cpus, 0);
	atomic_set(&mm->context.copros, 0);

	return 0;
}