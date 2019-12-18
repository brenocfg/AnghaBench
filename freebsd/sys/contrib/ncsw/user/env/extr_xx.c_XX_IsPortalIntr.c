#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {uintptr_t** portal_intr; } ;

/* Variables and functions */
 int MAXCPU ; 
 TYPE_1__ XX_PInfo ; 

__attribute__((used)) static bool
XX_IsPortalIntr(uintptr_t irq)
{
	int cpu, type;
	/* Check interrupt numbers of all available portals */
	for (type = 0; type < 2; type++)
		for (cpu = 0; cpu < MAXCPU; cpu++)
			if (irq == XX_PInfo.portal_intr[type][cpu])
				return (1);

	return (0);
}