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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int BUS_PROBE_NOWILDCARD ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spigen_probe(device_t dev)
{
	int rv;

	/*
	 * By default we only bid to attach if specifically added by our parent
	 * (usually via hint.spigen.#.at=busname).  On FDT systems we bid as the
	 * default driver based on being configured in the FDT data.
	 */
	rv = BUS_PROBE_NOWILDCARD;

#ifdef FDT
	if (ofw_bus_status_okay(dev) &&
	    ofw_bus_search_compatible(dev, compat_data)->ocd_data)
                rv = BUS_PROBE_DEFAULT;
#endif

	device_set_desc(dev, "SPI Generic IO");

	return (rv);
}