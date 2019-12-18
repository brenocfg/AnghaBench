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
 scalar_t__ CPUCLASS_686 ; 
 int CPUID_SSE2 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_class ; 
 int cpu_feature ; 
 int /*<<< orphan*/  i686_pagezero (void*) ; 
 int /*<<< orphan*/  sse2_pagezero (void*) ; 

__attribute__((used)) static __inline void
pagezero(void *page)
{
#if defined(I686_CPU)
	if (cpu_class == CPUCLASS_686) {
		if (cpu_feature & CPUID_SSE2)
			sse2_pagezero(page);
		else
			i686_pagezero(page);
	} else
#endif
		bzero(page, PAGE_SIZE);
}