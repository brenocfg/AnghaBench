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
struct clock_event_device {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIE_STIE ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  csr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clock_event_device* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  riscv_clock_event ; 
 int /*<<< orphan*/  riscv_timebase ; 
 int /*<<< orphan*/  sie ; 

__attribute__((used)) static int riscv_timer_starting_cpu(unsigned int cpu)
{
	struct clock_event_device *ce = per_cpu_ptr(&riscv_clock_event, cpu);

	ce->cpumask = cpumask_of(cpu);
	clockevents_config_and_register(ce, riscv_timebase, 100, 0x7fffffff);

	csr_set(sie, SIE_STIE);
	return 0;
}