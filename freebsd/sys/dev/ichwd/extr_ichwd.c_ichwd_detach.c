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
struct ichwd_softc {scalar_t__ smi_enabled; scalar_t__ gc_res; int /*<<< orphan*/  gc_rid; scalar_t__ gcs_res; int /*<<< orphan*/  gcs_rid; int /*<<< orphan*/  ich; scalar_t__ smi_res; int /*<<< orphan*/  smi_rid; scalar_t__ tco_res; int /*<<< orphan*/  tco_rid; int /*<<< orphan*/ * ev_tag; scalar_t__ active; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ichwd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichwd_smi_enable (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_sts_reset (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_tmr_disable (struct ichwd_softc*) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
ichwd_detach(device_t dev)
{
	struct ichwd_softc *sc;

	sc = device_get_softc(dev);

	/* halt the watchdog timer */
	if (sc->active)
		ichwd_tmr_disable(sc);

	/* enable the SMI handler */
	if (sc->smi_enabled != 0)
		ichwd_smi_enable(sc);

	/* deregister event handler */
	if (sc->ev_tag != NULL)
		EVENTHANDLER_DEREGISTER(watchdog_list, sc->ev_tag);
	sc->ev_tag = NULL;

	/* reset the watchdog status registers */
	ichwd_sts_reset(sc);

	/* deallocate I/O register space */
	bus_release_resource(dev, SYS_RES_IOPORT, sc->tco_rid, sc->tco_res);
	bus_release_resource(dev, SYS_RES_IOPORT, sc->smi_rid, sc->smi_res);

	/* deallocate memory resource */
	if (sc->gcs_res)
		bus_release_resource(sc->ich, SYS_RES_MEMORY, sc->gcs_rid,
		    sc->gcs_res);
	if (sc->gc_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->gc_rid,
		    sc->gc_res);

	return (0);
}