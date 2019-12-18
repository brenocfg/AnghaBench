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
struct TYPE_2__ {scalar_t__ cpu_die; } ;

/* Variables and functions */
 TYPE_1__** cpu_ops ; 
 int raw_smp_processor_id () ; 

__attribute__((used)) static bool have_cpu_die(void)
{
#ifdef CONFIG_HOTPLUG_CPU
	int any_cpu = raw_smp_processor_id();

	if (cpu_ops[any_cpu] && cpu_ops[any_cpu]->cpu_die)
		return true;
#endif
	return false;
}