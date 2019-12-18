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
struct octebus_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int cvm_oct_init_module (int /*<<< orphan*/ ) ; 
 struct octebus_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
octebus_attach(device_t dev)
{
	struct octebus_softc *sc;
	int rv;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	rv = cvm_oct_init_module(dev);
	if (rv != 0)
		return (ENXIO);

	return (0);
}