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
 struct cpumask CPU_MASK_NONE ; 
 int __send_ipi_mask (struct cpumask*,int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,struct cpumask*) ; 

__attribute__((used)) static bool __send_ipi_one(int cpu, int vector)
{
	struct cpumask mask = CPU_MASK_NONE;

	cpumask_set_cpu(cpu, &mask);
	return __send_ipi_mask(&mask, vector);
}