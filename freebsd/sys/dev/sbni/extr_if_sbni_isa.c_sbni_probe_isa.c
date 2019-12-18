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
struct sbni_softc {int /*<<< orphan*/  io_res; int /*<<< orphan*/  io_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SBNI_PORTS ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct sbni_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sbni_ids ; 
 scalar_t__ sbni_probe (struct sbni_softc*) ; 
 int /*<<< orphan*/  sbni_release_resources (struct sbni_softc*) ; 

__attribute__((used)) static int
sbni_probe_isa(device_t dev)
{
	struct sbni_softc *sc;
	int error;

	error = ISA_PNP_PROBE(device_get_parent(dev), dev, sbni_ids);
	if (error && error != ENOENT)
		return (error);

	sc = device_get_softc(dev);

 	sc->io_res = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT,
 						 &sc->io_rid, SBNI_PORTS,
 						 RF_ACTIVE);
	if (!sc->io_res) {
		printf("sbni: cannot allocate io ports!\n");
		return (ENOENT);
	}

	if (sbni_probe(sc) != 0) {
		sbni_release_resources(sc);
		return (ENXIO);
	}

	device_set_desc(dev, "Granch SBNI12/ISA adapter");
	return (0);
}