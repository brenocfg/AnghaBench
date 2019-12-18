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
 int /*<<< orphan*/  TSEC_MIIMIND_BUSY ; 
 int /*<<< orphan*/  TSEC_PHY_LOCK () ; 
 int /*<<< orphan*/  TSEC_PHY_UNLOCK () ; 
 int /*<<< orphan*/  TSEC_PHY_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TSEC_REG_MIIMADD ; 
 int /*<<< orphan*/  TSEC_REG_MIIMCON ; 
 struct tsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int tsec_mii_wait (struct tsec_softc*,int /*<<< orphan*/ ) ; 

int
tsec_miibus_writereg(device_t dev, int phy, int reg, int value)
{
	struct tsec_softc *sc;
	int timeout;

	sc = device_get_softc(dev);

	TSEC_PHY_LOCK();
	TSEC_PHY_WRITE(sc, TSEC_REG_MIIMADD, (phy << 8) | reg);
	TSEC_PHY_WRITE(sc, TSEC_REG_MIIMCON, value);
	timeout = tsec_mii_wait(sc, TSEC_MIIMIND_BUSY);
	TSEC_PHY_UNLOCK();

	if (timeout)
		device_printf(dev, "Timeout while writing to PHY!\n");

	return (0);
}