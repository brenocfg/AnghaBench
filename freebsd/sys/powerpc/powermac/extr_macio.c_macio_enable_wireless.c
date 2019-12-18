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
struct macio_softc {int /*<<< orphan*/  sc_memr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ KEYLARGO_EXTINT_GPIO_REG_BASE ; 
 int KEYLARGO_FCR2 ; 
 scalar_t__ KEYLARGO_GPIO_BASE ; 
 int bus_read_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int,int) ; 
 struct macio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
macio_enable_wireless(device_t dev, bool enable)
{
	struct macio_softc *sc = device_get_softc(dev);
	uint32_t x;

	if (enable) {
		x = bus_read_4(sc->sc_memr, KEYLARGO_FCR2);
		x |= 0x4;
		bus_write_4(sc->sc_memr, KEYLARGO_FCR2, x);

		/* Enable card slot. */
		bus_write_1(sc->sc_memr, KEYLARGO_GPIO_BASE + 0x0f, 5);
		DELAY(1000);
		bus_write_1(sc->sc_memr, KEYLARGO_GPIO_BASE + 0x0f, 4);
		DELAY(1000);
		x = bus_read_4(sc->sc_memr, KEYLARGO_FCR2);
		x &= ~0x80000000;

		bus_write_4(sc->sc_memr, KEYLARGO_FCR2, x);
		/* out8(gpio + 0x10, 4); */

		bus_write_1(sc->sc_memr, KEYLARGO_EXTINT_GPIO_REG_BASE + 0x0b, 0);
		bus_write_1(sc->sc_memr, KEYLARGO_EXTINT_GPIO_REG_BASE + 0x0a, 0x28);
		bus_write_1(sc->sc_memr, KEYLARGO_EXTINT_GPIO_REG_BASE + 0x0d, 0x28);
		bus_write_1(sc->sc_memr, KEYLARGO_GPIO_BASE + 0x0d, 0x28);
		bus_write_1(sc->sc_memr, KEYLARGO_GPIO_BASE + 0x0e, 0x28);
		bus_write_4(sc->sc_memr, 0x1c000, 0);

		/* Initialize the card. */
		bus_write_4(sc->sc_memr, 0x1a3e0, 0x41);
		x = bus_read_4(sc->sc_memr, KEYLARGO_FCR2);
		x |= 0x80000000;
		bus_write_4(sc->sc_memr, KEYLARGO_FCR2, x);
	} else {
		x = bus_read_4(sc->sc_memr, KEYLARGO_FCR2);
		x &= ~0x4;
		bus_write_4(sc->sc_memr, KEYLARGO_FCR2, x);
		/* out8(gpio + 0x10, 0); */
	}

	return (0);
}