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
 scalar_t__ cpuid_base ; 
 int /*<<< orphan*/  do_cpuid (scalar_t__,int*) ; 
 int /*<<< orphan*/  hypervisor_quirks (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void
hypervisor_version(void)
{
	uint32_t regs[4];
	int major, minor;

	do_cpuid(cpuid_base + 1, regs);

	major = regs[0] >> 16;
	minor = regs[0] & 0xffff;
	printf("XEN: Hypervisor version %d.%d detected.\n", major, minor);

	hypervisor_quirks(major, minor);
}