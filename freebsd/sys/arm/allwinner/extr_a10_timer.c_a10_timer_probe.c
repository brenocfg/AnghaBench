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
typedef  scalar_t__ u_int ;
struct a10_timer_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 scalar_t__ ALLWINNERSOC_SUN4I ; 
 scalar_t__ ALLWINNERSOC_SUN5I ; 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ allwinner_soc_family () ; 
 int /*<<< orphan*/  compat_data ; 
 struct a10_timer_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10_timer_probe(device_t dev)
{
	struct a10_timer_softc *sc;
#if defined(__arm__)
	u_int soc_family;
#endif

	sc = device_get_softc(dev);

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == 0)
		return (ENXIO);

#if defined(__arm__)
	/* For SoC >= A10 we have the ARM Timecounter/Eventtimer */
	soc_family = allwinner_soc_family();
	if (soc_family != ALLWINNERSOC_SUN4I &&
	    soc_family != ALLWINNERSOC_SUN5I)
		return (ENXIO);
#endif

	device_set_desc(dev, "Allwinner timer");
	return (BUS_PROBE_DEFAULT);
}