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
typedef  scalar_t__ vm_offset_t ;
struct gicv3_its_softc {scalar_t__* sc_pend_base; int /*<<< orphan*/  sc_cpus; } ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPI_PENDTAB_ALIGN ; 
 int /*<<< orphan*/  LPI_PENDTAB_MAX_ADDR ; 
 int /*<<< orphan*/  LPI_PENDTAB_SIZE ; 
 int /*<<< orphan*/  M_GICV3_ITS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ contigmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_dcache_wb_range (scalar_t__,int /*<<< orphan*/ ) ; 
 int mp_maxid ; 

__attribute__((used)) static void
gicv3_its_pendtables_init(struct gicv3_its_softc *sc)
{
	int i;

	for (i = 0; i <= mp_maxid; i++) {
		if (CPU_ISSET(i, &sc->sc_cpus) == 0)
			continue;

		sc->sc_pend_base[i] = (vm_offset_t)contigmalloc(
		    LPI_PENDTAB_SIZE, M_GICV3_ITS, M_WAITOK | M_ZERO,
		    0, LPI_PENDTAB_MAX_ADDR, LPI_PENDTAB_ALIGN, 0);

		/* Flush so the ITS can see the memory */
		cpu_dcache_wb_range((vm_offset_t)sc->sc_pend_base[i],
		    LPI_PENDTAB_SIZE);
	}
}