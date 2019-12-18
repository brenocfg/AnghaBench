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
 int CPUID2_CX16 ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int cpu_feature2 ; 

__attribute__((used)) static bool
pmap_di_locked(void)
{
	int tun;

	if ((cpu_feature2 & CPUID2_CX16) == 0)
		return (true);
	tun = 0;
	TUNABLE_INT_FETCH("vm.pmap.di_locked", &tun);
	return (tun != 0);
}