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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __boot_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_flag ; 

__attribute__((used)) static void arc_default_smp_cpu_kick(int cpu, unsigned long pc)
{
	BUG_ON(cpu == 0);

	__boot_write(wake_flag, cpu);
}