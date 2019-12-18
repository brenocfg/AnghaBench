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
typedef  int /*<<< orphan*/  xref ;
struct openpic_softc {int /*<<< orphan*/  sc_quirks; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPENPIC_QUIRK_HIDDEN_IRQS ; 
 int /*<<< orphan*/  OPENPIC_QUIRK_SINGLE_BIND ; 
 struct openpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int openpic_common_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
openpic_ofw_attach(device_t dev)
{
	struct openpic_softc *sc;
	phandle_t xref, node;

	node = ofw_bus_get_node(dev);
	sc = device_get_softc(dev);

	if (OF_getencprop(node, "phandle", &xref, sizeof(xref)) == -1 &&
	    OF_getencprop(node, "ibm,phandle", &xref, sizeof(xref)) == -1 &&
	    OF_getencprop(node, "linux,phandle", &xref, sizeof(xref)) == -1)
		xref = node;
	
	if (ofw_bus_is_compatible(dev, "fsl,mpic")) {
		sc->sc_quirks = OPENPIC_QUIRK_SINGLE_BIND;
		sc->sc_quirks |= OPENPIC_QUIRK_HIDDEN_IRQS;
	}

	return (openpic_common_attach(dev, xref));
}