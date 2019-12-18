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
struct thunder_pem_softc {int /*<<< orphan*/ * reg; int /*<<< orphan*/  mem_rman; int /*<<< orphan*/  io_rman; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_free_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct thunder_pem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
thunder_pem_release_all(device_t dev)
{
	struct thunder_pem_softc *sc;

	sc = device_get_softc(dev);

	rman_fini(&sc->io_rman);
	rman_fini(&sc->mem_rman);

	if (sc->reg != NULL)
		bus_free_resource(dev, SYS_RES_MEMORY, sc->reg);
}