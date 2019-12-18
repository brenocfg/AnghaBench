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
struct ofw_pcib_gen_softc {scalar_t__ ops_node; int /*<<< orphan*/  ops_iinfo; TYPE_1__ ops_pcib_sc; } ;
typedef  int /*<<< orphan*/  ofw_pci_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct ofw_pcib_gen_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_setup_iinfo (scalar_t__,int /*<<< orphan*/ *,int) ; 

void
ofw_pcib_gen_setup(device_t bridge)
{
	struct ofw_pcib_gen_softc *sc;

	sc = device_get_softc(bridge);
	sc->ops_pcib_sc.dev = bridge;
	sc->ops_node = ofw_bus_get_node(bridge);
	KASSERT(sc->ops_node != 0,
	    ("ofw_pcib_gen_setup: no ofw pci parent bus!"));

	ofw_bus_setup_iinfo(sc->ops_node, &sc->ops_iinfo,
	    sizeof(ofw_pci_intr_t));
}