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
struct gic_v3_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ GICD_IPRIORITYR (size_t) ; 
 scalar_t__ GICR_ICENABLER0 ; 
 scalar_t__ GICR_IGROUPR0 ; 
 scalar_t__ GICR_ISENABLER0 ; 
 int GICR_I_ENABLER_PPI_MASK ; 
 int GICR_I_ENABLER_SGI_MASK ; 
 scalar_t__ GICR_I_PER_IPRIORITYn ; 
 scalar_t__ GICR_SGI_BASE_SIZE ; 
 size_t GIC_LAST_PPI ; 
 int GIC_PRIORITY_MAX ; 
 int /*<<< orphan*/  REDIST ; 
 int /*<<< orphan*/  gic_r_write (struct gic_v3_softc*,int,scalar_t__,int) ; 
 int gic_v3_redist_find (struct gic_v3_softc*) ; 
 int gic_v3_redist_wake (struct gic_v3_softc*) ; 
 int /*<<< orphan*/  gic_v3_wait_for_rwp (struct gic_v3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_redist_init(struct gic_v3_softc *sc)
{
	int err;
	size_t i;

	err = gic_v3_redist_find(sc);
	if (err != 0)
		return (err);

	err = gic_v3_redist_wake(sc);
	if (err != 0)
		return (err);

	/* Configure SGIs and PPIs to be Group1 Non-secure */
	gic_r_write(sc, 4, GICR_SGI_BASE_SIZE + GICR_IGROUPR0,
	    0xFFFFFFFF);

	/* Disable SPIs */
	gic_r_write(sc, 4, GICR_SGI_BASE_SIZE + GICR_ICENABLER0,
	    GICR_I_ENABLER_PPI_MASK);
	/* Enable SGIs */
	gic_r_write(sc, 4, GICR_SGI_BASE_SIZE + GICR_ISENABLER0,
	    GICR_I_ENABLER_SGI_MASK);

	/* Set priority for SGIs and PPIs */
	for (i = 0; i <= GIC_LAST_PPI; i += GICR_I_PER_IPRIORITYn) {
		gic_r_write(sc, 4, GICR_SGI_BASE_SIZE + GICD_IPRIORITYR(i),
		    GIC_PRIORITY_MAX);
	}

	gic_v3_wait_for_rwp(sc, REDIST);

	return (0);
}