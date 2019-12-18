#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  phandle_t ;
struct TYPE_5__ {int num_ports; int fixed_mask; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,void*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ e6000sw_parse_ethernet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e6000sw_parse_fixed_link (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
e6000sw_parse_child_fdt(e6000sw_softc_t *sc, phandle_t child, int *pport)
{
	uint32_t port;

	if (pport == NULL)
		return (ENXIO);

	if (OF_getencprop(child, "reg", (void *)&port, sizeof(port)) < 0)
		return (ENXIO);
	if (port >= sc->num_ports)
		return (ENXIO);
	*pport = port;

	if (e6000sw_parse_fixed_link(sc, child, port) != 0)
		return (ENXIO);

	if (e6000sw_parse_ethernet(sc, child, port) != 0)
		return (ENXIO);

	if ((sc->fixed_mask & (1 << port)) != 0)
		device_printf(sc->dev, "fixed port at %d\n", port);
	else
		device_printf(sc->dev, "PHY at port %d\n", port);

	return (0);
}