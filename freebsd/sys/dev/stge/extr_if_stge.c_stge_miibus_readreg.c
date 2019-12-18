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
struct stge_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_1 (struct stge_softc*,int) ; 
 int /*<<< orphan*/  STGE_MII_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_MII_UNLOCK (struct stge_softc*) ; 
 int STGE_PhyCtrl ; 
 struct stge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mii_bitbang_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stge_mii_bitbang_ops ; 

__attribute__((used)) static int
stge_miibus_readreg(device_t dev, int phy, int reg)
{
	struct stge_softc *sc;
	int error, val;

	sc = device_get_softc(dev);

	if (reg == STGE_PhyCtrl) {
		/* XXX allow ip1000phy read STGE_PhyCtrl register. */
		STGE_MII_LOCK(sc);
		error = CSR_READ_1(sc, STGE_PhyCtrl);
		STGE_MII_UNLOCK(sc);
		return (error);
	}

	STGE_MII_LOCK(sc);
	val = mii_bitbang_readreg(dev, &stge_mii_bitbang_ops, phy, reg);
	STGE_MII_UNLOCK(sc);
	return (val);
}