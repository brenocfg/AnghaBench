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
 int /*<<< orphan*/  arch_send_wakeup_ipi_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_logical_map (unsigned int) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emev2_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	arch_send_wakeup_ipi_mask(cpumask_of(cpu_logical_map(cpu)));
	return 0;
}