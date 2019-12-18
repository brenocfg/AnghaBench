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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ldt; } ;
struct mm_struct {TYPE_1__ context; } ;
struct ldt_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_ldt ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_struct*,int) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,struct ldt_struct*) ; 

__attribute__((used)) static void install_ldt(struct mm_struct *mm, struct ldt_struct *ldt)
{
	mutex_lock(&mm->context.lock);

	/* Synchronizes with READ_ONCE in load_mm_ldt. */
	smp_store_release(&mm->context.ldt, ldt);

	/* Activate the LDT for all CPUs using currents mm. */
	on_each_cpu_mask(mm_cpumask(mm), flush_ldt, mm, true);

	mutex_unlock(&mm->context.lock);
}