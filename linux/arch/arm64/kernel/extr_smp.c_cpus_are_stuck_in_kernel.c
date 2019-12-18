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
 int /*<<< orphan*/  cpus_stuck_in_kernel ; 
 int /*<<< orphan*/  have_cpu_die () ; 
 int num_possible_cpus () ; 

bool cpus_are_stuck_in_kernel(void)
{
	bool smp_spin_tables = (num_possible_cpus() > 1 && !have_cpu_die());

	return !!cpus_stuck_in_kernel || smp_spin_tables;
}