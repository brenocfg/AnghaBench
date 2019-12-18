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
typedef  int uint64_t ;
typedef  scalar_t__ u_int ;
struct gic_v3_softc {scalar_t__ gic_nirqs; } ;

/* Variables and functions */
 int CPU_AFFINITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIST ; 
 int /*<<< orphan*/  GICD_CTLR ; 
 int GICD_CTLR_ARE_NS ; 
 int GICD_CTLR_G1 ; 
 int GICD_CTLR_G1A ; 
 int /*<<< orphan*/  GICD_ICENABLER (scalar_t__) ; 
 int /*<<< orphan*/  GICD_ICFGR (scalar_t__) ; 
 int /*<<< orphan*/  GICD_IGROUPR (scalar_t__) ; 
 int /*<<< orphan*/  GICD_IPRIORITYR (scalar_t__) ; 
 int /*<<< orphan*/  GICD_IROUTER (scalar_t__) ; 
 scalar_t__ GICD_I_PER_ICFGRn ; 
 scalar_t__ GICD_I_PER_IGROUPRn ; 
 scalar_t__ GICD_I_PER_IPRIORITYn ; 
 scalar_t__ GICD_I_PER_ISENABLERn ; 
 scalar_t__ GIC_FIRST_SPI ; 
 int GIC_PRIORITY_MAX ; 
 int /*<<< orphan*/  gic_d_write (struct gic_v3_softc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gic_v3_wait_for_rwp (struct gic_v3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_dist_init(struct gic_v3_softc *sc)
{
	uint64_t aff;
	u_int i;

	/*
	 * 1. Disable the Distributor
	 */
	gic_d_write(sc, 4, GICD_CTLR, 0);
	gic_v3_wait_for_rwp(sc, DIST);

	/*
	 * 2. Configure the Distributor
	 */
	/* Set all SPIs to be Group 1 Non-secure */
	for (i = GIC_FIRST_SPI; i < sc->gic_nirqs; i += GICD_I_PER_IGROUPRn)
		gic_d_write(sc, 4, GICD_IGROUPR(i), 0xFFFFFFFF);

	/* Set all global interrupts to be level triggered, active low. */
	for (i = GIC_FIRST_SPI; i < sc->gic_nirqs; i += GICD_I_PER_ICFGRn)
		gic_d_write(sc, 4, GICD_ICFGR(i), 0x00000000);

	/* Set priority to all shared interrupts */
	for (i = GIC_FIRST_SPI;
	    i < sc->gic_nirqs; i += GICD_I_PER_IPRIORITYn) {
		/* Set highest priority */
		gic_d_write(sc, 4, GICD_IPRIORITYR(i), GIC_PRIORITY_MAX);
	}

	/*
	 * Disable all interrupts. Leave PPI and SGIs as they are enabled in
	 * Re-Distributor registers.
	 */
	for (i = GIC_FIRST_SPI; i < sc->gic_nirqs; i += GICD_I_PER_ISENABLERn)
		gic_d_write(sc, 4, GICD_ICENABLER(i), 0xFFFFFFFF);

	gic_v3_wait_for_rwp(sc, DIST);

	/*
	 * 3. Enable Distributor
	 */
	/* Enable Distributor with ARE, Group 1 */
	gic_d_write(sc, 4, GICD_CTLR, GICD_CTLR_ARE_NS | GICD_CTLR_G1A |
	    GICD_CTLR_G1);

	/*
	 * 4. Route all interrupts to boot CPU.
	 */
	aff = CPU_AFFINITY(0);
	for (i = GIC_FIRST_SPI; i < sc->gic_nirqs; i++)
		gic_d_write(sc, 4, GICD_IROUTER(i), aff);

	return (0);
}