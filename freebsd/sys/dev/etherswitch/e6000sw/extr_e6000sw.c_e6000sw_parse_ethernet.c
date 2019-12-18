#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  switch_eth_handle ;
typedef  scalar_t__ phandle_t ;
struct TYPE_4__ {int cpuports_mask; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */
 scalar_t__ OF_getencprop (scalar_t__,char*,void*,int) ; 
 scalar_t__ OF_node_from_xref (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int e6000sw_parse_fixed_link (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static int
e6000sw_parse_ethernet(e6000sw_softc_t *sc, phandle_t port_handle, uint32_t port) {
	phandle_t switch_eth, switch_eth_handle;

	if (OF_getencprop(port_handle, "ethernet", (void*)&switch_eth_handle,
	    sizeof(switch_eth_handle)) > 0) {
		if (switch_eth_handle > 0) {
			switch_eth = OF_node_from_xref(switch_eth_handle);

			device_printf(sc->dev, "CPU port at %d\n", port);
			sc->cpuports_mask |= (1 << port);

			return (e6000sw_parse_fixed_link(sc, switch_eth, port));
		} else
			device_printf(sc->dev,
				"Port %d has ethernet property but it points "
				"to an invalid location\n", port);
	}

	return (0);
}