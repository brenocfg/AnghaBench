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
struct chipc_softc {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPC_CHIPCTRL ; 
 int /*<<< orphan*/  CHIPC_LOCK (struct chipc_softc*) ; 
 int /*<<< orphan*/  CHIPC_UNLOCK (struct chipc_softc*) ; 
 int bhnd_bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chipc_write_chipctrl(device_t dev, uint32_t value, uint32_t mask)
{
	struct chipc_softc	*sc;
	uint32_t		 cctrl;

	sc = device_get_softc(dev);

	CHIPC_LOCK(sc);

	cctrl = bhnd_bus_read_4(sc->core, CHIPC_CHIPCTRL);
	cctrl = (cctrl & ~mask) | (value | mask);
	bhnd_bus_write_4(sc->core, CHIPC_CHIPCTRL, cctrl);

	CHIPC_UNLOCK(sc);
}