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
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmobile_boot_scu ; 
 int /*<<< orphan*/  shmobile_scu_base_phys ; 
 int /*<<< orphan*/  shmobile_smp_hook (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shmobile_scu_cpu_prepare(unsigned int cpu)
{
	/* For this particular CPU register SCU SMP boot vector */
	shmobile_smp_hook(cpu, __pa_symbol(shmobile_boot_scu),
			  shmobile_scu_base_phys);
	return 0;
}