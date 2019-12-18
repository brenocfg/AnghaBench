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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __cpuid (int*,int) ; 

extern void pt_cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx,
		     uint32_t *ecx, uint32_t *edx)
{
	int cpu_info[4];

	__cpuid(cpu_info, leaf);
	*eax = cpu_info[0];
	*ebx = cpu_info[1];
	*ecx = cpu_info[2];
	*edx = cpu_info[3];
}