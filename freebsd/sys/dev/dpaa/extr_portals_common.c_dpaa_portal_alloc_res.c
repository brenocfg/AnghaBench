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
struct resource_list_entry {scalar_t__ start; int /*<<< orphan*/  count; scalar_t__ end; } ;
struct resource_list {int dummy; } ;
struct dpaa_portals_softc {int* sc_rrid; TYPE_1__* sc_dp; scalar_t__ sc_dp_pa; int /*<<< orphan*/ ** sc_rres; } ;
struct dpaa_portals_devinfo {int /*<<< orphan*/  di_intr_pol; int /*<<< orphan*/  di_intr_trig; struct resource_list di_res; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int dp_regs_mapped; int dp_irid; int /*<<< orphan*/ * dp_ires; scalar_t__ dp_intr_num; int /*<<< orphan*/  dp_ci_size; scalar_t__ dp_ci_pa; int /*<<< orphan*/  dp_ce_size; scalar_t__ dp_ce_pa; } ;

/* Variables and functions */
 int ENXIO ; 
 int E_OK ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int XX_MallocSmartInit () ; 
 int XX_PreallocAndBindIntr (uintptr_t,int) ; 
 int /*<<< orphan*/  _TLB_ENTRY_IO ; 
 int /*<<< orphan*/  _TLB_ENTRY_MEM ; 
 void* bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_config_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct dpaa_portals_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb1_set_entry (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dpaa_portal_alloc_res(device_t dev, struct dpaa_portals_devinfo *di, int cpu)
{
	struct dpaa_portals_softc *sc = device_get_softc(dev);
	struct resource_list_entry *rle;
	int err;
	struct resource_list *res;

	/* Check if MallocSmart allocator is ready */
	if (XX_MallocSmartInit() != E_OK)
		return (ENXIO);

	res = &di->di_res;

	/*
	 * Allocate memory.
	 * Reserve only one pair of CE/CI virtual memory regions
	 * for all CPUs, in order to save the space.
	 */
	if (sc->sc_rres[0] == NULL) {
		/* Cache enabled area */
		rle = resource_list_find(res, SYS_RES_MEMORY, 0);
		sc->sc_rrid[0] = 0;
		sc->sc_rres[0] = bus_alloc_resource(dev,
		    SYS_RES_MEMORY, &sc->sc_rrid[0], rle->start + sc->sc_dp_pa,
		    rle->end + sc->sc_dp_pa, rle->count, RF_ACTIVE);
		if (sc->sc_rres[0] == NULL) {
			device_printf(dev,
			    "Could not allocate cache enabled memory.\n");
			return (ENXIO);
		}
		tlb1_set_entry(rman_get_bushandle(sc->sc_rres[0]),
		    rle->start + sc->sc_dp_pa, rle->count, _TLB_ENTRY_MEM);
		/* Cache inhibited area */
		rle = resource_list_find(res, SYS_RES_MEMORY, 1);
		sc->sc_rrid[1] = 1;
		sc->sc_rres[1] = bus_alloc_resource(dev,
		    SYS_RES_MEMORY, &sc->sc_rrid[1], rle->start + sc->sc_dp_pa,
		    rle->end + sc->sc_dp_pa, rle->count, RF_ACTIVE);
		if (sc->sc_rres[1] == NULL) {
			device_printf(dev,
			    "Could not allocate cache inhibited memory.\n");
			bus_release_resource(dev, SYS_RES_MEMORY,
			    sc->sc_rrid[0], sc->sc_rres[0]);
			return (ENXIO);
		}
		tlb1_set_entry(rman_get_bushandle(sc->sc_rres[1]),
		    rle->start + sc->sc_dp_pa, rle->count, _TLB_ENTRY_IO);
		sc->sc_dp[cpu].dp_regs_mapped = 1;
	}
	/* Acquire portal's CE_PA and CI_PA */
	rle = resource_list_find(res, SYS_RES_MEMORY, 0);
	sc->sc_dp[cpu].dp_ce_pa = rle->start + sc->sc_dp_pa;
	sc->sc_dp[cpu].dp_ce_size = rle->count;
	rle = resource_list_find(res, SYS_RES_MEMORY, 1);
	sc->sc_dp[cpu].dp_ci_pa = rle->start + sc->sc_dp_pa;
	sc->sc_dp[cpu].dp_ci_size = rle->count;

	/* Allocate interrupts */
	rle = resource_list_find(res, SYS_RES_IRQ, 0);
	sc->sc_dp[cpu].dp_irid = 0;
	sc->sc_dp[cpu].dp_ires = bus_alloc_resource(dev,
	    SYS_RES_IRQ, &sc->sc_dp[cpu].dp_irid, rle->start, rle->end,
	    rle->count, RF_ACTIVE);
	/* Save interrupt number for later use */
	sc->sc_dp[cpu].dp_intr_num = rle->start;

	if (sc->sc_dp[cpu].dp_ires == NULL) {
		device_printf(dev, "Could not allocate irq.\n");
		return (ENXIO);
	}

	err = XX_PreallocAndBindIntr((uintptr_t)sc->sc_dp[cpu].dp_ires, cpu);

	if (err != E_OK) {
		device_printf(dev, "Could not prealloc and bind interrupt\n");
		bus_release_resource(dev, SYS_RES_IRQ,
		    sc->sc_dp[cpu].dp_irid, sc->sc_dp[cpu].dp_ires);
		sc->sc_dp[cpu].dp_ires = NULL;
		return (ENXIO);
	}

#if 0
	err = bus_generic_config_intr(dev, rle->start, di->di_intr_trig,
	    di->di_intr_pol);
	if (err != 0) {
		device_printf(dev, "Could not configure interrupt\n");
		bus_release_resource(dev, SYS_RES_IRQ,
		    sc->sc_dp[cpu].dp_irid, sc->sc_dp[cpu].dp_ires);
		sc->sc_dp[cpu].dp_ires = NULL;
		return (err);
	}
#endif

	return (0);
}