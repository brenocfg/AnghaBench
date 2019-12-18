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
struct tsec_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int TSEC_MIIMCOM_READCYCLE ; 
 int TSEC_MIIMIND_BUSY ; 
 int TSEC_MIIMIND_NOTVALID ; 
 int /*<<< orphan*/  TSEC_PHY_LOCK () ; 
 int TSEC_PHY_READ (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSEC_PHY_UNLOCK () ; 
 int /*<<< orphan*/  TSEC_PHY_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TSEC_REG_MIIMADD ; 
 int /*<<< orphan*/  TSEC_REG_MIIMCOM ; 
 int /*<<< orphan*/  TSEC_REG_MIIMSTAT ; 
 struct tsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int tsec_mii_wait (struct tsec_softc*,int) ; 

int
tsec_miibus_readreg(device_t dev, int phy, int reg)
{
	struct tsec_softc *sc;
	int timeout;
	int rv;

	sc = device_get_softc(dev);

	TSEC_PHY_LOCK();
	TSEC_PHY_WRITE(sc, TSEC_REG_MIIMADD, (phy << 8) | reg);
	TSEC_PHY_WRITE(sc, TSEC_REG_MIIMCOM, 0);
	TSEC_PHY_WRITE(sc, TSEC_REG_MIIMCOM, TSEC_MIIMCOM_READCYCLE);

	timeout = tsec_mii_wait(sc, TSEC_MIIMIND_NOTVALID | TSEC_MIIMIND_BUSY);
	rv = TSEC_PHY_READ(sc, TSEC_REG_MIIMSTAT);
	TSEC_PHY_UNLOCK();

	if (timeout)
		device_printf(dev, "Timeout while reading from PHY!\n");

	return (rv);
}