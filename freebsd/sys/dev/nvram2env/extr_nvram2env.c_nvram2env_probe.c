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
typedef  int uint32_t ;
struct nvram2env_softc {scalar_t__ sig; scalar_t__ maxsize; int flags; int addr; int need_swap; int crc; scalar_t__ bsh; int /*<<< orphan*/ * bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_SPECIFIC ; 
 scalar_t__ CFE_NVRAM_SIGNATURE ; 
 int ENXIO ; 
 int NVRAM_FLAGS_GENERIC ; 
 int NVRAM_FLAGS_UBOOT ; 
 scalar_t__ NVRAM_MAX_SIZE ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bus_space_read_4 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 struct nvram2env_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ htole32 (int) ; 
 scalar_t__ resource_int_value (char*,int /*<<< orphan*/ ,char*,int*) ; 

int
nvram2env_probe(device_t dev)
{
	uint32_t i, ivar, sig;
	struct nvram2env_softc * sc = device_get_softc(dev);

	/*
	 * Please ensure that your implementation of NVRAM->ENV specifies
	 * bus tag
	 */
	if (sc->bst == NULL)
		return (ENXIO);

	if (sc->sig == 0)
		if (resource_int_value("nvram", device_get_unit(dev), "sig",
		    &sc->sig) != 0 || sc->sig == 0)
			sc->sig = CFE_NVRAM_SIGNATURE;

	if (sc->maxsize == 0)
		if (resource_int_value("nvram", device_get_unit(dev), "maxsize",
		    &sc->maxsize) != 0 || sc->maxsize == 0)
			sc->maxsize = NVRAM_MAX_SIZE;

	if (sc->flags == 0)
		if (resource_int_value("nvram", device_get_unit(dev), "flags",
		    &sc->flags) != 0 || sc->flags == 0)
			sc->flags = NVRAM_FLAGS_GENERIC;


	for (i = 0; i < 2; i ++)
	{
		switch (i) {
		case 0:
			break;
		case 1:
		case 2:
			if (resource_int_value("nvram", device_get_unit(dev),
			    (i == 1) ? "base" : "fallbackbase", &ivar) != 0 ||
			    ivar == 0)
				continue;

			sc->addr = ivar;
			break;
		default:
			break;
		}

		if (sc->addr == 0)
			continue;

		if (bootverbose)
			device_printf(dev, "base=0x%08x sig=0x%08x "
			    "maxsize=0x%08x flags=0x%08x\n",
			    sc->addr, sc->sig, sc->maxsize, sc->flags);

		if (bus_space_map(sc->bst, sc->addr, sc->maxsize, 0,
		    &sc->bsh) != 0)
			continue;

		sig = bus_space_read_4(sc->bst, sc->bsh, 0);
		if ( sig == sc->sig /*FLSH*/)
		{
			device_printf(dev, "Found NVRAM at %#x\n", 
			    (uint32_t)ivar);
			sc->need_swap = 0;
			goto unmap_done;
		}
		else if ( htole32(sig) == sc->sig /*HSLF*/)
		{
			device_printf(dev, "Found NVRAM at %#x\n", 
			    (uint32_t)ivar);
			sc->need_swap = 1;
			goto unmap_done;
		} else if (sc->flags & NVRAM_FLAGS_UBOOT) {
			device_printf(dev, "Use NVRAM at %#x\n", 
			    (uint32_t)ivar);
			sc->crc = sig;
			goto unmap_done;
		}
		bus_space_unmap(sc->bst, sc->bsh, NVRAM_MAX_SIZE);
	}
	sc->bst = 0;
	sc->bsh = 0;
	sc->addr = 0;
	return (ENXIO);

unmap_done:
	bus_space_unmap(sc->bst, sc->bsh, NVRAM_MAX_SIZE);
	device_set_desc(dev, "NVRAM to ENV pseudo-device");
	return (BUS_PROBE_SPECIFIC);

}