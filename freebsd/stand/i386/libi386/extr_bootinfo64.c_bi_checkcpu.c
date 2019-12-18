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
 unsigned int AMDID_LM ; 
 int /*<<< orphan*/  AMD_VENDOR_ID ; 
 int /*<<< orphan*/  CENTAUR_VENDOR_ID ; 
 int /*<<< orphan*/  INTEL_VENDOR_ID ; 
 int PSL_ID ; 
 int /*<<< orphan*/  do_cpuid (int,unsigned int*) ; 
 int read_eflags () ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_eflags (int) ; 

__attribute__((used)) static int
bi_checkcpu(void)
{
    char *cpu_vendor;
    int vendor[3];
    int eflags;
    unsigned int regs[4];

    /* Check for presence of "cpuid". */
    eflags = read_eflags();
    write_eflags(eflags ^ PSL_ID);
    if (!((eflags ^ read_eflags()) & PSL_ID))
	return (0);

    /* Fetch the vendor string. */
    do_cpuid(0, regs);
    vendor[0] = regs[1];
    vendor[1] = regs[3];
    vendor[2] = regs[2];
    cpu_vendor = (char *)vendor;

    /* Check for vendors that support AMD features. */
    if (strncmp(cpu_vendor, INTEL_VENDOR_ID, 12) != 0 &&
	strncmp(cpu_vendor, AMD_VENDOR_ID, 12) != 0 &&
	strncmp(cpu_vendor, CENTAUR_VENDOR_ID, 12) != 0)
	return (0);

    /* Has to support AMD features. */
    do_cpuid(0x80000000, regs);
    if (!(regs[0] >= 0x80000001))
	return (0);

    /* Check for long mode. */
    do_cpuid(0x80000001, regs);
    return (regs[3] & AMDID_LM);
}