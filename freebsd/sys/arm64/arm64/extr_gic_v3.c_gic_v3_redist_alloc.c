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
typedef  size_t u_int ;
struct TYPE_2__ {int /*<<< orphan*/ ** pcpu; } ;
struct gic_v3_softc {TYPE_1__ gic_redists; } ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_GIC_V3 ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t mp_maxid ; 

__attribute__((used)) static int
gic_v3_redist_alloc(struct gic_v3_softc *sc)
{
	u_int cpuid;

	/* Allocate struct resource for all CPU's Re-Distributor registers */
	for (cpuid = 0; cpuid <= mp_maxid; cpuid++)
		if (CPU_ISSET(cpuid, &all_cpus) != 0)
			sc->gic_redists.pcpu[cpuid] =
				malloc(sizeof(*sc->gic_redists.pcpu[0]),
				    M_GIC_V3, M_WAITOK);
		else
			sc->gic_redists.pcpu[cpuid] = NULL;
	return (0);
}