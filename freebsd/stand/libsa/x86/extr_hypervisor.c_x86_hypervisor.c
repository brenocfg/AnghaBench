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
 int CPUID2_HV ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 

const char *
x86_hypervisor(void)
{
	static union {
		struct {
			u_int high;
			char name[13];
		} hv;
		u_int regs[4];
	} u;

	/* Return NULL when no hypervisor is present. */
	do_cpuid(1, u.regs);
	if ((u.regs[2] & CPUID2_HV) == 0)
		return (NULL);
	/* Return the hypervisor's identification. */
	do_cpuid(0x40000000, u.regs);
	return (u.hv.name);
}