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
typedef  int /*<<< orphan*/  u32 ;
struct msr {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rwmsr_on_cpus (struct cpumask const*,int /*<<< orphan*/ ,struct msr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wrmsr_on_cpu ; 

void wrmsr_on_cpus(const struct cpumask *mask, u32 msr_no, struct msr *msrs)
{
	__rwmsr_on_cpus(mask, msr_no, msrs, __wrmsr_on_cpu);
}