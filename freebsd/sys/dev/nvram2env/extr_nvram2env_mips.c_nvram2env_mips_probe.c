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
struct nvram2env_softc {int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct nvram2env_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_bus_space_generic ; 
 int nvram2env_probe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvram2env_mips_probe(device_t dev)
{
	struct nvram2env_softc	*sc;

	sc = device_get_softc(dev);
	sc->bst = mips_bus_space_generic;

	return (nvram2env_probe(dev));
}