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
typedef  int /*<<< orphan*/  uint32_t ;
struct rk_pinctrl_softc {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 
 struct rk_pinctrl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_pinctrl_configure_pin (struct rk_pinctrl_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rk_pinctrl_configure_pins(device_t dev, phandle_t cfgxref)
{
	struct rk_pinctrl_softc *sc;
	phandle_t node;
	uint32_t *pins;
	int i, npins;

	sc = device_get_softc(dev);
	node = OF_node_from_xref(cfgxref);

	npins = OF_getencprop_alloc_multi(node, "rockchip,pins",  sizeof(*pins),
	    (void **)&pins);
	if (npins <= 0)
		return (ENOENT);

	for (i = 0; i != npins; i += 4)
		rk_pinctrl_configure_pin(sc, pins + i);

	return (0);
}