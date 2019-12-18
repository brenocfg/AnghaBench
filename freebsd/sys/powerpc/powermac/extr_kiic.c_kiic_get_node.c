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
struct kiic_softc {int /*<<< orphan*/  sc_node; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct kiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static phandle_t
kiic_get_node(device_t bus, device_t dev)
{
	struct kiic_softc *sc;

	sc = device_get_softc(bus);
	/* We only have one child, the I2C bus, which needs our own node. */
		
	return sc->sc_node;
}