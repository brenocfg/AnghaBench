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
struct TYPE_2__ {int /*<<< orphan*/ * pcpu; } ;
struct gic_v3_softc {uintptr_t gic_nirqs; uintptr_t gic_nchildren; uintptr_t gic_bus; int /*<<< orphan*/  gic_pidr2; TYPE_1__ gic_redists; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 uintptr_t GICR_PIDR2_ARCH (int /*<<< orphan*/ ) ; 
 uintptr_t GICR_PIDR2_ARCH_GICv3 ; 
 uintptr_t GICR_PIDR2_ARCH_GICv4 ; 
#define  GICV3_IVAR_NIRQS 131 
#define  GICV3_IVAR_REDIST 130 
 uintptr_t GIC_BUS_MAX ; 
 uintptr_t GIC_BUS_UNKNOWN ; 
#define  GIC_IVAR_BUS 129 
#define  GIC_IVAR_HW_REV 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 uintptr_t NIRQ ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct gic_v3_softc *sc;

	sc = device_get_softc(dev);

	switch (which) {
	case GICV3_IVAR_NIRQS:
		*result = (NIRQ - sc->gic_nirqs) / sc->gic_nchildren;
		return (0);
	case GICV3_IVAR_REDIST:
		*result = (uintptr_t)sc->gic_redists.pcpu[PCPU_GET(cpuid)];
		return (0);
	case GIC_IVAR_HW_REV:
		KASSERT(
		    GICR_PIDR2_ARCH(sc->gic_pidr2) == GICR_PIDR2_ARCH_GICv3 ||
		    GICR_PIDR2_ARCH(sc->gic_pidr2) == GICR_PIDR2_ARCH_GICv4,
		    ("gic_v3_read_ivar: Invalid GIC architecture: %d (%.08X)",
		     GICR_PIDR2_ARCH(sc->gic_pidr2), sc->gic_pidr2));
		*result = GICR_PIDR2_ARCH(sc->gic_pidr2);
		return (0);
	case GIC_IVAR_BUS:
		KASSERT(sc->gic_bus != GIC_BUS_UNKNOWN,
		    ("gic_v3_read_ivar: Unknown bus type"));
		KASSERT(sc->gic_bus <= GIC_BUS_MAX,
		    ("gic_v3_read_ivar: Invalid bus type %u", sc->gic_bus));
		*result = sc->gic_bus;
		return (0);
	}

	return (ENOENT);
}