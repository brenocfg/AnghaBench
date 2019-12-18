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

/* Variables and functions */
 int /*<<< orphan*/ * cpu_foreign_map ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ r4k_op_needs_ipi (unsigned int) ; 
 int /*<<< orphan*/  smp_call_function_many (int /*<<< orphan*/ *,void (*) (void*),void*,int) ; 
 size_t smp_processor_id () ; 

__attribute__((used)) static inline void r4k_on_each_cpu(unsigned int type,
				   void (*func)(void *info), void *info)
{
	preempt_disable();
	if (r4k_op_needs_ipi(type))
		smp_call_function_many(&cpu_foreign_map[smp_processor_id()],
				       func, info, 1);
	func(info);
	preempt_enable();
}