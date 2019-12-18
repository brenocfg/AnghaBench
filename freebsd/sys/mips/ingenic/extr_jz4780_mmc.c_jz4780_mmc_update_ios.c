#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmc_ios {int bus_width; scalar_t__ clock; } ;
struct TYPE_2__ {struct mmc_ios ios; } ;
struct jz4780_mmc_softc {int /*<<< orphan*/  sc_cmdat; TYPE_1__ sc_host; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_BUS_1BIT ; 
 int /*<<< orphan*/  JZ_BUS_4BIT ; 
 int /*<<< orphan*/  JZ_BUS_8BIT ; 
 int /*<<< orphan*/  JZ_BUS_WIDTH_M ; 
#define  bus_width_1 130 
#define  bus_width_4 129 
#define  bus_width_8 128 
 struct jz4780_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int jz4780_mmc_config_clock (struct jz4780_mmc_softc*,scalar_t__) ; 

__attribute__((used)) static int
jz4780_mmc_update_ios(device_t bus, device_t child)
{
	struct jz4780_mmc_softc *sc;
	struct mmc_ios *ios;
	int error;

	sc = device_get_softc(bus);
	ios = &sc->sc_host.ios;
	if (ios->clock) {
		/* Set the MMC clock. */
		error = jz4780_mmc_config_clock(sc, ios->clock);
		if (error != 0)
			return (error);
	}

	/* Set the bus width. */
	switch (ios->bus_width) {
	case bus_width_1:
		sc->sc_cmdat &= ~(JZ_BUS_WIDTH_M);
		sc->sc_cmdat |= JZ_BUS_1BIT;
		break;
	case bus_width_4:
		sc->sc_cmdat &= ~(JZ_BUS_WIDTH_M);
		sc->sc_cmdat |= JZ_BUS_4BIT;
		break;
	case bus_width_8:
		sc->sc_cmdat &= ~(JZ_BUS_WIDTH_M);
		sc->sc_cmdat |= JZ_BUS_8BIT;
		break;
	}
	return (0);
}