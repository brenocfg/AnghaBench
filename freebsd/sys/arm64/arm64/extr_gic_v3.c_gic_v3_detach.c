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
struct TYPE_2__ {int nregions; int /*<<< orphan*/ * regions; int /*<<< orphan*/ ** pcpu; } ;
struct gic_v3_softc {TYPE_1__ gic_redists; int /*<<< orphan*/ * gic_res; scalar_t__ gic_registered; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_GIC_V3 ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t mp_maxid ; 
 int /*<<< orphan*/  panic (char*) ; 

int
gic_v3_detach(device_t dev)
{
	struct gic_v3_softc *sc;
	size_t i;
	int rid;

	sc = device_get_softc(dev);

	if (device_is_attached(dev)) {
		/*
		 * XXX: We should probably deregister PIC
		 */
		if (sc->gic_registered)
			panic("Trying to detach registered PIC");
	}
	for (rid = 0; rid < (sc->gic_redists.nregions + 1); rid++)
		bus_release_resource(dev, SYS_RES_MEMORY, rid, sc->gic_res[rid]);

	for (i = 0; i <= mp_maxid; i++)
		free(sc->gic_redists.pcpu[i], M_GIC_V3);

	free(sc->gic_res, M_GIC_V3);
	free(sc->gic_redists.regions, M_GIC_V3);

	return (0);
}