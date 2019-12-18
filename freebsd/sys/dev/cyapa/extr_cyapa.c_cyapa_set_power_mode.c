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
typedef  int uint8_t ;
struct cyapa_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_POWER_MODE ; 
 int /*<<< orphan*/  IIC_WAIT ; 
 int cyapa_read_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int cyapa_write_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cyapa_set_power_mode(struct cyapa_softc *sc, int mode)
{
	uint8_t data;
	device_t bus;
	int error;

	bus = device_get_parent(sc->dev);
	error = iicbus_request_bus(bus, sc->dev, IIC_WAIT);
	if (error == 0) {
		error = cyapa_read_bytes(sc->dev, CMD_POWER_MODE,
		    &data, 1);
		data = (data & ~0xFC) | mode;
		if (error == 0) {
			error = cyapa_write_bytes(sc->dev, CMD_POWER_MODE,
			    &data, 1);
		}
		iicbus_release_bus(bus, sc->dev);
	}
}