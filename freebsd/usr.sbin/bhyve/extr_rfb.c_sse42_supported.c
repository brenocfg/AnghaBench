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
typedef  int u_int ;

/* Variables and functions */
 int CPUID2_SSE42 ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 

__attribute__((used)) static int
sse42_supported(void)
{
	u_int cpu_registers[4], ecx;

	do_cpuid(1, cpu_registers);

	ecx = cpu_registers[2];

	return ((ecx & CPUID2_SSE42) != 0);
}