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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct armada_thermal_softc {int /*<<< orphan*/  chip_temperature; int /*<<< orphan*/  temp_upd; int /*<<< orphan*/  temp_upd_mtx; int /*<<< orphan*/ * ctrl_res; int /*<<< orphan*/ * stat_res; TYPE_1__* tdata; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* tsen_init ) (struct armada_thermal_softc*) ;} ;
typedef  TYPE_1__ armada_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTRL_RID ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int STAT_RID ; 
 int /*<<< orphan*/  SYSCTL_ADD_LONG (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  armada_temp_update ; 
 scalar_t__ armada_tsen_get_temp (struct armada_thermal_softc*,int /*<<< orphan*/ *) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct armada_thermal_softc*) ; 
 struct armada_thermal_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct armada_thermal_softc*) ; 

__attribute__((used)) static int
armada_thermal_attach(device_t dev)
{
	struct armada_thermal_softc *sc;
	const armada_tdata_t *tdata;
	struct sysctl_ctx_list *sctx;
	struct sysctl_oid_list *schildren;
	int timeout;
	int rid;

	sc = device_get_softc(dev);

	/* Allocate CTRL and STAT register spaces */
	rid = STAT_RID;
	sc->stat_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (sc->stat_res == NULL) {
		device_printf(dev,
		    "Could not allocate memory for the status register\n");
		return (ENXIO);
	}

	rid = CTRL_RID;
	sc->ctrl_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (sc->ctrl_res == NULL) {
		device_printf(dev,
		    "Could not allocate memory for the control register\n");
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->stat_res), sc->stat_res);
		sc->stat_res = NULL;
		return (ENXIO);
	}

	/* Now initialize the sensor */
	tdata = sc->tdata;
	tdata->tsen_init(sc);
	/* Set initial temperature value */
	for (timeout = 1000; timeout > 0; timeout--) {
		if (armada_tsen_get_temp(sc, &sc->chip_temperature) == 0)
			break;
		DELAY(10);
	}
	if (timeout <= 0) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->stat_res), sc->stat_res);
		sc->stat_res = NULL;
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->ctrl_res), sc->ctrl_res);
		sc->ctrl_res = NULL;
		return (ENXIO);
	}
	/* Initialize mutex */
	mtx_init(&sc->temp_upd_mtx, "Armada Thermal", NULL, MTX_DEF);
	/* Set up the temperature update callout */
	callout_init_mtx(&sc->temp_upd, &sc->temp_upd_mtx, 0);
	/* Schedule callout */
	callout_reset(&sc->temp_upd, hz, armada_temp_update, sc);

	sctx = device_get_sysctl_ctx(dev);
	schildren = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	SYSCTL_ADD_LONG(sctx, schildren, OID_AUTO, "temperature",
	    CTLFLAG_RD, &sc->chip_temperature, "SoC temperature");

	return (0);
}