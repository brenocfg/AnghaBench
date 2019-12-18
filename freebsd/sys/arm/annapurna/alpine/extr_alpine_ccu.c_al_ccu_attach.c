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
struct al_ccu_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AL_CCU_SNOOP_CONTROL_IOFAB_0_OFFSET ; 
 int /*<<< orphan*/  AL_CCU_SNOOP_CONTROL_IOFAB_1_OFFSET ; 
 int /*<<< orphan*/  AL_CCU_SPECULATION_CONTROL_OFFSET ; 
 int /*<<< orphan*/  al_ccu_spec ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct al_ccu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
al_ccu_attach(device_t dev)
{
	struct al_ccu_softc *sc;
	int err;

	sc = device_get_softc(dev);

	err = bus_alloc_resources(dev, al_ccu_spec, &sc->res);
	if (err != 0) {
		device_printf(dev, "could not allocate resources\n");
		return (err);
	}

	/* Enable cache snoop */
	bus_write_4(sc->res, AL_CCU_SNOOP_CONTROL_IOFAB_0_OFFSET, 1);
	bus_write_4(sc->res, AL_CCU_SNOOP_CONTROL_IOFAB_1_OFFSET, 1);

	/* Disable speculative fetches from masters */
	bus_write_4(sc->res, AL_CCU_SPECULATION_CONTROL_OFFSET, 7);

	return (0);
}