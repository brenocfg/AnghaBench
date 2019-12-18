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
struct task_struct {int dummy; } ;

/* Variables and functions */
 unsigned long THREAD_SIZE ; 
 scalar_t__* hardirq_ctx ; 
 scalar_t__* softirq_ctx ; 
 unsigned long task_cpu (struct task_struct*) ; 

__attribute__((used)) static inline int valid_irq_stack(unsigned long sp, struct task_struct *p,
				  unsigned long nbytes)
{
	unsigned long stack_page;
	unsigned long cpu = task_cpu(p);

	stack_page = (unsigned long)hardirq_ctx[cpu];
	if (sp >= stack_page && sp <= stack_page + THREAD_SIZE - nbytes)
		return 1;

	stack_page = (unsigned long)softirq_ctx[cpu];
	if (sp >= stack_page && sp <= stack_page + THREAD_SIZE - nbytes)
		return 1;

	return 0;
}