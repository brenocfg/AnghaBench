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
typedef  union savefpu {int dummy; } savefpu ;
typedef  void* u_int ;

/* Variables and functions */
 void* cpu_feature2 ; 
 int cpu_max_ext_state_size ; 
 int /*<<< orphan*/  cpuid_count (int,int,void**) ; 
 int /*<<< orphan*/  do_cpuid (int,void**) ; 
 scalar_t__ use_xsave ; 

__attribute__((used)) static void
npxinit_bsp2(void)
{
	u_int cp[4];

	if (use_xsave) {
		cpuid_count(0xd, 0x0, cp);
		cpu_max_ext_state_size = cp[1];

		/*
		 * Reload the cpu_feature2, since we enabled OSXSAVE.
		 */
		do_cpuid(1, cp);
		cpu_feature2 = cp[2];
	} else
		cpu_max_ext_state_size = sizeof(union savefpu);
}