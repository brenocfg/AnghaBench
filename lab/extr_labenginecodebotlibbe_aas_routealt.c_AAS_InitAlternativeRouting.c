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

void AAS_InitAlternativeRouting(void)
{
#ifdef ENABLE_ALTROUTING
	if (midrangeareas) FreeMemory(midrangeareas);
	midrangeareas = (midrangearea_t *) GetMemory(aasworld.numareas * sizeof(midrangearea_t));
	if (clusterareas) FreeMemory(clusterareas);
	clusterareas = (int *) GetMemory(aasworld.numareas * sizeof(int));
#endif
}