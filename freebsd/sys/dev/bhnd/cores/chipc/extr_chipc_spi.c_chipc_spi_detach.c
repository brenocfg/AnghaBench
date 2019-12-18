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
struct chipc_spi_softc {int /*<<< orphan*/  sc_flash_res; int /*<<< orphan*/  sc_flash_rid; int /*<<< orphan*/  sc_res; int /*<<< orphan*/  sc_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct chipc_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_spi_detach(device_t dev)
{
	struct chipc_spi_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	if ((error = bus_generic_detach(dev)))
		return (error);

	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rid, sc->sc_res);
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_flash_rid,
	    sc->sc_flash_res);
	return (0);
}