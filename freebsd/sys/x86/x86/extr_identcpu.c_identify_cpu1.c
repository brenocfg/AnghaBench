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
typedef  void* u_int ;

/* Variables and functions */
 void* cpu_feature ; 
 void* cpu_feature2 ; 
 void* cpu_high ; 
 void* cpu_id ; 
 void* cpu_procinfo ; 
 char* cpu_vendor ; 
 int /*<<< orphan*/  do_cpuid (int,void**) ; 

void
identify_cpu1(void)
{
	u_int regs[4];

	do_cpuid(0, regs);
	cpu_high = regs[0];
	((u_int *)&cpu_vendor)[0] = regs[1];
	((u_int *)&cpu_vendor)[1] = regs[3];
	((u_int *)&cpu_vendor)[2] = regs[2];
	cpu_vendor[12] = '\0';

	do_cpuid(1, regs);
	cpu_id = regs[0];
	cpu_procinfo = regs[1];
	cpu_feature = regs[3];
	cpu_feature2 = regs[2];
}