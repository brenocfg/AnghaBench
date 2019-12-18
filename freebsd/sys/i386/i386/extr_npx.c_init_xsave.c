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
 int CPUID2_XSAVE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int cpu_feature2 ; 
 int /*<<< orphan*/  cpu_fxsr ; 
 int use_xsave ; 

__attribute__((used)) static void
init_xsave(void)
{

	if (use_xsave)
		return;
	if (!cpu_fxsr || (cpu_feature2 & CPUID2_XSAVE) == 0)
		return;
	use_xsave = 1;
	TUNABLE_INT_FETCH("hw.use_xsave", &use_xsave);
}