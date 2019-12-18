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
 int CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlt_cpus_mask ; 

__attribute__((used)) static int
g_eli_cpu_is_disabled(int cpu)
{
#ifdef SMP
	return (CPU_ISSET(cpu, &hlt_cpus_mask));
#else
	return (0);
#endif
}