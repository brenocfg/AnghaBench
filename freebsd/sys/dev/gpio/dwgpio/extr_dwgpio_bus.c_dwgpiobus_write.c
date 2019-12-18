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
struct dwgpiobus_softc {int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dwgpiobus_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dwgpiobus_write(device_t dev, bus_size_t offset, int val)
{
	struct dwgpiobus_softc *sc;

	sc = device_get_softc(dev);

	bus_write_4(sc->res[0], offset, val);

	return (0);
}