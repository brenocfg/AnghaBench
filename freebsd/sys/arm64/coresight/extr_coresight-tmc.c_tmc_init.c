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
struct tmc_softc {int etf_configured; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORESIGHT_ETF ; 
 int /*<<< orphan*/  CORESIGHT_ETR ; 
 int /*<<< orphan*/  CORESIGHT_LAR ; 
 int /*<<< orphan*/  CORESIGHT_UNKNOWN ; 
 int /*<<< orphan*/  CORESIGHT_UNLOCK ; 
#define  DEVID_CONFIGTYPE_ETF 129 
#define  DEVID_CONFIGTYPE_ETR 128 
 int DEVID_CONFIGTYPE_M ; 
 int /*<<< orphan*/  TMC_DEVID ; 
 int /*<<< orphan*/  TMC_LAR ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tmc_configure_etf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tmc_init(device_t dev)
{
	struct tmc_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	/* Unlock Coresight */
	bus_write_4(sc->res, CORESIGHT_LAR, CORESIGHT_UNLOCK);

	/* Unlock TMC */
	bus_write_4(sc->res, TMC_LAR, CORESIGHT_UNLOCK);

	reg = bus_read_4(sc->res, TMC_DEVID);
	reg &= DEVID_CONFIGTYPE_M;
	switch (reg) {
	case DEVID_CONFIGTYPE_ETR:
		sc->dev_type = CORESIGHT_ETR;
		dprintf(dev, "ETR configuration found\n");
		break;
	case DEVID_CONFIGTYPE_ETF:
		sc->dev_type = CORESIGHT_ETF;
		dprintf(dev, "ETF configuration found\n");
		if (sc->etf_configured == false) {
			tmc_configure_etf(dev);
			sc->etf_configured = true;
		}
		break;
	default:
		sc->dev_type = CORESIGHT_UNKNOWN;
		break;
	}

	return (0);
}