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
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cpu_possible_mask ; 

__attribute__((used)) static cpumask_t cpu_coregroup_map(int cpu)
{
	/*
	 * Presently all SH-X3 SMP cores are multi-cores, so just keep it
	 * simple until we have a method for determining topology..
	 */
	return *cpu_possible_mask;
}