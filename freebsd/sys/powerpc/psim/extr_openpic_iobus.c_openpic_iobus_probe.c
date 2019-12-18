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
struct openpic_softc {int sc_psim; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OPENPIC_DEVSTR ; 
 struct openpic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* iobus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
openpic_iobus_probe(device_t dev)
{
	struct openpic_softc *sc;
	char *name;

	name = iobus_get_name(dev);
	if (strcmp(name, "interrupt-controller") != 0)
		return (ENXIO);

	/*
	 * The description was already printed out in the nexus
	 * probe, so don't do it again here
	 */
	device_set_desc(dev, OPENPIC_DEVSTR);

	sc = device_get_softc(dev);
	sc->sc_psim = 1;

	return (0);
}