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
 int /*<<< orphan*/  IPI_CPU_STOP ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int /*<<< orphan*/ ,struct cpumask*) ; 
 int /*<<< orphan*/  cpumask_copy (struct cpumask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipi_send_msg (struct cpumask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void smp_send_stop(void)
{
	struct cpumask targets;
	cpumask_copy(&targets, cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), &targets);
	ipi_send_msg(&targets, IPI_CPU_STOP);
}