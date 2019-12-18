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
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secondary_startup_arm ; 
 int zynq_cpun_start (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int zynq_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	return zynq_cpun_start(__pa_symbol(secondary_startup_arm), cpu);
}