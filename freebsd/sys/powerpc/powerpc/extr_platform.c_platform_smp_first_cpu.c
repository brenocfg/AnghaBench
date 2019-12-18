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
struct cpuref {int dummy; } ;

/* Variables and functions */
 int PLATFORM_SMP_FIRST_CPU (int /*<<< orphan*/ ,struct cpuref*) ; 
 int /*<<< orphan*/  plat_obj ; 

int
platform_smp_first_cpu(struct cpuref *cpu)
{
	return (PLATFORM_SMP_FIRST_CPU(plat_obj, cpu));
}