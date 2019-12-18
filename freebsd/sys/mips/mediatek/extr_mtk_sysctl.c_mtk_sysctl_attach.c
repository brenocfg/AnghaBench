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
struct mtk_sysctl_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * mem_res; scalar_t__ mem_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTK_SYSCTL_LOCK_INIT (struct mtk_sysctl_softc*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct mtk_sysctl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtk_sysctl_detach (int /*<<< orphan*/ ) ; 
 struct mtk_sysctl_softc* mtk_sysctl_sc ; 

__attribute__((used)) static int
mtk_sysctl_attach(device_t dev)
{
	struct mtk_sysctl_softc *sc = device_get_softc(dev);

	if (device_get_unit(dev) != 0 || mtk_sysctl_sc != NULL) {
		device_printf(dev, "Only one sysctl module supported\n");
		return (ENXIO);
	}

	mtk_sysctl_sc = sc;

	/* Map control/status registers. */
	sc->mem_rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->mem_rid, RF_ACTIVE);

	if (sc->mem_res == NULL) {
		device_printf(dev, "couldn't map memory\n");
		mtk_sysctl_detach(dev);
		return (ENXIO);
	}

	sc->dev = dev;

	MTK_SYSCTL_LOCK_INIT(sc);

	return (0);
}