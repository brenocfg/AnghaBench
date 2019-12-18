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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ofw_pcib_softc {int /*<<< orphan*/  ops_iinfo; int /*<<< orphan*/  ops_node; TYPE_1__ ops_pcib_sc; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell_t ;

/* Variables and functions */
 struct ofw_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_setup_iinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pcib_attach_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_attach_common (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofw_pcib_pci_attach(device_t dev)
{
	struct ofw_pcib_softc *sc;

	sc = device_get_softc(dev);
	sc->ops_pcib_sc.dev = dev;
	sc->ops_node = ofw_bus_get_node(dev);

	ofw_bus_setup_iinfo(sc->ops_node, &sc->ops_iinfo,
	    sizeof(cell_t));

	pcib_attach_common(dev);
	return (pcib_attach_child(dev));
}