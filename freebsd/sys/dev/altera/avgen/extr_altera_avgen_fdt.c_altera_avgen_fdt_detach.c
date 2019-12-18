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
struct altera_avgen_softc {int /*<<< orphan*/  avg_res; int /*<<< orphan*/  avg_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  altera_avgen_detach (struct altera_avgen_softc*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct altera_avgen_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
altera_avgen_fdt_detach(device_t dev)
{
	struct altera_avgen_softc *sc;

	sc = device_get_softc(dev);
	altera_avgen_detach(sc);
	bus_release_resource(dev, SYS_RES_MEMORY, sc->avg_rid, sc->avg_res);
	return (0);
}