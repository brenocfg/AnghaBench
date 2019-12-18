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
typedef  scalar_t__ uint32_t ;
struct task_struct {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ __pa_symbol (int /*<<< orphan*/ ) ; 
 int alpine_cpu_wakeup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cpu_logical_map (unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__*) ; 
 int /*<<< orphan*/  secondary_startup ; 

__attribute__((used)) static int alpine_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	phys_addr_t addr;

	addr = __pa_symbol(secondary_startup);

	if (addr > (phys_addr_t)(uint32_t)(-1)) {
		pr_err("FAIL: resume address over 32bit (%pa)", &addr);
		return -EINVAL;
	}

	return alpine_cpu_wakeup(cpu_logical_map(cpu), (uint32_t)addr);
}