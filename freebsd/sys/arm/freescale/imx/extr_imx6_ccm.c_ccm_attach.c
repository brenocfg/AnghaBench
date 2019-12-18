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
typedef  int uint32_t ;
struct ccm_softc {int /*<<< orphan*/ * mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_CGPR ; 
 int CCM_CGPR_INT_MEM_CLK_LPM ; 
 int /*<<< orphan*/  CCM_CLPCR ; 
 int CCM_CLPCR_LPM_MASK ; 
 int CCM_CLPCR_LPM_RUN ; 
 int ENXIO ; 
 int RD4 (struct ccm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WR4 (struct ccm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccm_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccm_init_gates (struct ccm_softc*) ; 
 struct ccm_softc* ccm_sc ; 
 struct ccm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ccm_attach(device_t dev)
{
	struct ccm_softc *sc;
	int err, rid;
	uint32_t reg;

	sc = device_get_softc(dev);
	err = 0;

	/* Allocate bus_space resources. */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		err = ENXIO;
		goto out;
	}

	ccm_sc = sc;

	/*
	 * Configure the Low Power Mode setting to leave the ARM core power on
	 * when a WFI instruction is executed.  This lets the MPCore timers and
	 * GIC continue to run, which is helpful when the only thing that can
	 * wake you up is an MPCore Private Timer interrupt delivered via GIC.
	 *
	 * XXX Based on the docs, setting CCM_CGPR_INT_MEM_CLK_LPM shouldn't be
	 * required when the LPM bits are set to LPM_RUN.  But experimentally
	 * I've experienced a fairly rare lockup when not setting it.  I was
	 * unable to prove conclusively that the lockup was related to power
	 * management or that this definitively fixes it.  Revisit this.
	 */
	reg = RD4(sc, CCM_CGPR);
	reg |= CCM_CGPR_INT_MEM_CLK_LPM;
	WR4(sc, CCM_CGPR, reg);
	reg = RD4(sc, CCM_CLPCR);
	reg = (reg & ~CCM_CLPCR_LPM_MASK) | CCM_CLPCR_LPM_RUN;
	WR4(sc, CCM_CLPCR, reg);

	ccm_init_gates(sc);

	err = 0;

out:

	if (err != 0)
		ccm_detach(dev);

	return (err);
}