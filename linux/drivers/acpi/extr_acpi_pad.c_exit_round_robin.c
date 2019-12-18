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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear_cpu (int,struct cpumask*) ; 
 int /*<<< orphan*/  pad_busy_cpus_bits ; 
 struct cpumask* to_cpumask (int /*<<< orphan*/ ) ; 
 int* tsk_in_cpu ; 

__attribute__((used)) static void exit_round_robin(unsigned int tsk_index)
{
	struct cpumask *pad_busy_cpus = to_cpumask(pad_busy_cpus_bits);
	cpumask_clear_cpu(tsk_in_cpu[tsk_index], pad_busy_cpus);
	tsk_in_cpu[tsk_index] = -1;
}