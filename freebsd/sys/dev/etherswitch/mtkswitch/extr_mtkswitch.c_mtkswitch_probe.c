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
struct mtkswitch_softc {scalar_t__ sc_switchtype; } ;
typedef  scalar_t__ mtk_switch_type ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ MTK_SWITCH_NONE ; 
 int /*<<< orphan*/  bzero (struct mtkswitch_softc*,int) ; 
 int /*<<< orphan*/  compat_data ; 
 struct mtkswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtkswitch_probe(device_t dev)
{
	struct mtkswitch_softc *sc;
	mtk_switch_type switch_type;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	switch_type = ofw_bus_search_compatible(dev, compat_data)->ocd_data;
	if (switch_type == MTK_SWITCH_NONE)
		return (ENXIO);

	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));
	sc->sc_switchtype = switch_type;

	device_set_desc_copy(dev, "MTK Switch Driver");

	return (0);
}