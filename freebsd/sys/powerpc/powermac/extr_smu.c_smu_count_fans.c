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
struct smu_softc {int /*<<< orphan*/ * sc_fans; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 int /*<<< orphan*/  OF_getprop (scalar_t__,char*,char*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 struct smu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_fill_fan_prop (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
smu_count_fans(device_t dev)
{
	struct smu_softc *sc;
	phandle_t child, node, root;
	int nfans = 0;

	node = ofw_bus_get_node(dev);
	sc = device_get_softc(dev);

	/* First find the fanroots and count the number of fans. */
	for (root = OF_child(node); root != 0; root = OF_peer(root)) {
		char name[32];
		memset(name, 0, sizeof(name));
		OF_getprop(root, "name", name, sizeof(name));
		if (strncmp(name, "rpm-fans", 9) == 0 ||
		    strncmp(name, "pwm-fans", 9) == 0 ||
		    strncmp(name, "fans", 5) == 0)
			for (child = OF_child(root); child != 0;
			     child = OF_peer(child)) {
				nfans++;
				/* When allocated, fill the fan properties. */
				if (sc->sc_fans != NULL) {
					smu_fill_fan_prop(dev, child,
							  nfans - 1);
				}
			}
	}
	if (nfans == 0) {
		device_printf(dev, "WARNING: No fans detected!\n");
		return (0);
	}
	return (nfans);
}