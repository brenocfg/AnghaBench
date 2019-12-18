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
struct pcpu {int dummy; } ;

/* Variables and functions */
 int PLATFORM_SMP_START_CPU (int /*<<< orphan*/ ,struct pcpu*) ; 
 int /*<<< orphan*/  plat_obj ; 

int
platform_smp_start_cpu(struct pcpu *cpu)
{
	return (PLATFORM_SMP_START_CPU(plat_obj, cpu));
}