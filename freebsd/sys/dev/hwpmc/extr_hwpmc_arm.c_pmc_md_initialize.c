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
struct pmc_mdep {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPU_CLASS_CORTEXA ; 
 scalar_t__ cpu_class ; 
 struct pmc_mdep* pmc_armv7_initialize () ; 

struct pmc_mdep *
pmc_md_initialize()
{
#ifdef CPU_CORTEXA
	if (cpu_class == CPU_CLASS_CORTEXA)
		return pmc_armv7_initialize();
#endif
	return NULL;
}