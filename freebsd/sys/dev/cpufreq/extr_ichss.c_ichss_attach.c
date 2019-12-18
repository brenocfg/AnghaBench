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
typedef  int uint16_t ;
struct ichss_softc {int bm_rid; int ctrl_rid; TYPE_1__* sets; int /*<<< orphan*/ * bm_reg; int /*<<< orphan*/ * ctrl_reg; void* dev; } ;
typedef  int /*<<< orphan*/  ss_en ;
typedef  void* device_t ;
struct TYPE_2__ {int lat; void* dev; void* power; void* volts; void* freq; } ;

/* Variables and functions */
 void* CPUFREQ_VAL_UNKNOWN ; 
 int ENXIO ; 
 int ICHSS_ENABLE ; 
 int /*<<< orphan*/  ICHSS_PMCFG_OFFSET ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpufreq_register (void*) ; 
 struct ichss_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  ich_device ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ichss_attach(device_t dev)
{
	struct ichss_softc *sc;
	uint16_t ss_en;

	sc = device_get_softc(dev);
	sc->dev = dev;

	sc->bm_rid = 0;
	sc->bm_reg = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &sc->bm_rid,
	    RF_ACTIVE);
	if (sc->bm_reg == NULL) {
		device_printf(dev, "failed to alloc BM arb register\n");
		return (ENXIO);
	}
	sc->ctrl_rid = 1;
	sc->ctrl_reg = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
	    &sc->ctrl_rid, RF_ACTIVE);
	if (sc->ctrl_reg == NULL) {
		device_printf(dev, "failed to alloc control register\n");
		bus_release_resource(dev, SYS_RES_IOPORT, sc->bm_rid,
		    sc->bm_reg);
		return (ENXIO);
	}

	/* Activate SpeedStep control if not already enabled. */
	ss_en = pci_read_config(ich_device, ICHSS_PMCFG_OFFSET, sizeof(ss_en));
	if ((ss_en & ICHSS_ENABLE) == 0) {
		device_printf(dev, "enabling SpeedStep support\n");
		pci_write_config(ich_device, ICHSS_PMCFG_OFFSET,
		    ss_en | ICHSS_ENABLE, sizeof(ss_en));
	}

	/* Setup some defaults for our exported settings. */
	sc->sets[0].freq = CPUFREQ_VAL_UNKNOWN;
	sc->sets[0].volts = CPUFREQ_VAL_UNKNOWN;
	sc->sets[0].power = CPUFREQ_VAL_UNKNOWN;
	sc->sets[0].lat = 1000;
	sc->sets[0].dev = dev;
	sc->sets[1] = sc->sets[0];
	cpufreq_register(dev);

	return (0);
}