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
struct ichwd_softc {int /*<<< orphan*/ * gc_res; int /*<<< orphan*/  gc_rid; int /*<<< orphan*/ * gcs_res; int /*<<< orphan*/  gcs_rid; int /*<<< orphan*/  ich; int /*<<< orphan*/ * smi_res; int /*<<< orphan*/  smi_rid; int /*<<< orphan*/ * tco_res; int /*<<< orphan*/  tco_rid; int /*<<< orphan*/  smi_enabled; int /*<<< orphan*/  ev_tag; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ichwd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TCO2_STS ; 
 int TCO_SECOND_TO_STS ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ichwd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ichwd_clear_noreboot (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_event ; 
 scalar_t__ ichwd_lpc_attach (int /*<<< orphan*/ ) ; 
 int ichwd_read_tco_2 (struct ichwd_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ichwd_smb_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichwd_smi_disable (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_smi_is_enabled (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_sts_reset (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_tmr_disable (struct ichwd_softc*) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
ichwd_attach(device_t dev)
{
	struct ichwd_softc *sc;

	sc = device_get_softc(dev);
	sc->device = dev;

	if (ichwd_lpc_attach(dev) != 0 && ichwd_smb_attach(dev) != 0)
		goto fail;

	if (ichwd_clear_noreboot(sc) != 0)
		goto fail;

	/*
	 * Determine if we are coming up after a watchdog-induced reset.  Some
	 * BIOSes may clear this bit at bootup, preventing us from reporting
	 * this case on such systems.  We clear this bit in ichwd_sts_reset().
	 */
	if ((ichwd_read_tco_2(sc, TCO2_STS) & TCO_SECOND_TO_STS) != 0)
		device_printf(dev,
		    "resuming after hardware watchdog timeout\n");

	/* reset the watchdog status registers */
	ichwd_sts_reset(sc);

	/* make sure the WDT starts out inactive */
	ichwd_tmr_disable(sc);

	/* register the watchdog event handler */
	sc->ev_tag = EVENTHANDLER_REGISTER(watchdog_list, ichwd_event, sc, 0);

	/* disable the SMI handler */
	sc->smi_enabled = ichwd_smi_is_enabled(sc);
	ichwd_smi_disable(sc);

	return (0);
 fail:
	sc = device_get_softc(dev);
	if (sc->tco_res != NULL)
		bus_release_resource(dev, SYS_RES_IOPORT,
		    sc->tco_rid, sc->tco_res);
	if (sc->smi_res != NULL)
		bus_release_resource(dev, SYS_RES_IOPORT,
		    sc->smi_rid, sc->smi_res);
	if (sc->gcs_res != NULL)
		bus_release_resource(sc->ich, SYS_RES_MEMORY,
		    sc->gcs_rid, sc->gcs_res);
	if (sc->gc_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->gc_rid, sc->gc_res);

	return (ENXIO);
}