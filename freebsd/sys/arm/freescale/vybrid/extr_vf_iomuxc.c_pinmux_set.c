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
struct iomuxc_softc {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMUXC (int) ; 
 int MAX_MUX_LEN ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getencprop (scalar_t__,char*,int*,int) ; 
 int OF_getproplen (scalar_t__,char*) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  WRITE4 (struct iomuxc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ofw_bus_node_status_okay (scalar_t__) ; 

__attribute__((used)) static int
pinmux_set(struct iomuxc_softc *sc)
{
	phandle_t child, parent, root;
	pcell_t iomux_config[MAX_MUX_LEN];
	int len;
	int values;
	int pin;
	int pin_cfg;
	int i;

	root = OF_finddevice("/");
	len = 0;
	parent = root;

	/* Find 'iomux_config' prop in the nodes */
	for (child = OF_child(parent); child != 0; child = OF_peer(child)) {

		/* Find a 'leaf'. Start the search from this node. */
		while (OF_child(child)) {
			parent = child;
			child = OF_child(child);
		}

		if (!ofw_bus_node_status_okay(child))
			continue;

		if ((len = OF_getproplen(child, "iomux_config")) > 0) {
			OF_getencprop(child, "iomux_config", iomux_config, len);

			values = len / (sizeof(uint32_t));
			for (i = 0; i < values; i += 2) {
				pin = iomux_config[i];
				pin_cfg = iomux_config[i+1];
#if 0
				device_printf(sc->dev, "Set pin %d to 0x%08x\n",
				    pin, pin_cfg);
#endif
				WRITE4(sc, IOMUXC(pin), pin_cfg);
			}
		}

		if (OF_peer(child) == 0) {
			/* No more siblings. */
			child = parent;
			parent = OF_parent(child);
		}
	}

	return (0);
}