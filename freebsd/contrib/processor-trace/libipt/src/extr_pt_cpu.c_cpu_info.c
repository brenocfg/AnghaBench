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

/* Variables and functions */
 int /*<<< orphan*/  pt_cpuid (unsigned int,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static uint32_t cpu_info(void)
{
	uint32_t eax, ebx, ecx, edx;

	eax = 0;
	ebx = 0;
	ecx = 0;
	edx = 0;
	pt_cpuid(1u, &eax, &ebx, &ecx, &edx);

	return eax;
}