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
struct arm_gicv2m_softc {int /*<<< orphan*/  sc_xref; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int arm_gicv2m_attach (int /*<<< orphan*/ ) ; 
 struct arm_gicv2m_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_gicv2m_fdt_attach(device_t dev)
{
	struct arm_gicv2m_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_xref = OF_xref_from_node(ofw_bus_get_node(dev));

	return (arm_gicv2m_attach(dev));
}