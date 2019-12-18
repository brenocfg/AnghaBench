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
 scalar_t__ is_percpu_thread () ; 
 int smp_processor_id () ; 
 int work_on_cpu (int,long (*) (void*),void*) ; 

__attribute__((used)) static int call_on_cpu(int cpu, long (*fn)(void *), void *arg, bool direct)
{
	if (direct || (is_percpu_thread() && cpu == smp_processor_id()))
		return fn(arg);
	return work_on_cpu(cpu, fn, arg);
}