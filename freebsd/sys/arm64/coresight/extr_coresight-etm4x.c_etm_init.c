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
struct etm_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORESIGHT_LAR ; 
 int /*<<< orphan*/  CORESIGHT_UNLOCK ; 
 int /*<<< orphan*/  TRCIDR (int) ; 
 int TRCIDR1_TRCARCHMAJ_M ; 
 int TRCIDR1_TRCARCHMAJ_S ; 
 int TRCIDR1_TRCARCHMIN_M ; 
 int TRCIDR1_TRCARCHMIN_S ; 
 int /*<<< orphan*/  TRCOSLAR ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct etm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int,int) ; 

__attribute__((used)) static int
etm_init(device_t dev)
{
	struct etm_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	/* Unlocking Coresight */
	bus_write_4(sc->res, CORESIGHT_LAR, CORESIGHT_UNLOCK);

	/* Unlocking ETM */
	bus_write_4(sc->res, TRCOSLAR, 0);

	reg = bus_read_4(sc->res, TRCIDR(1));
	dprintf("ETM Version: %d.%d\n",
	    (reg & TRCIDR1_TRCARCHMAJ_M) >> TRCIDR1_TRCARCHMAJ_S,
	    (reg & TRCIDR1_TRCARCHMIN_M) >> TRCIDR1_TRCARCHMIN_S);

	return (0);
}