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
typedef  int /*<<< orphan*/  uWord ;
struct mos_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOS_DPRINTFN (char*) ; 
 int /*<<< orphan*/  MOS_LOCK (struct mos_softc*) ; 
 int MOS_PHYCTL_PHYADDR ; 
 int MOS_PHYCTL_READ ; 
 int MOS_PHYSTS_PENDING ; 
 int MOS_PHYSTS_PHYREG ; 
 int MOS_PHYSTS_READY ; 
 int /*<<< orphan*/  MOS_PHY_CTL ; 
 int /*<<< orphan*/  MOS_PHY_DATA ; 
 int /*<<< orphan*/  MOS_PHY_STS ; 
 int MOS_TIMEOUT ; 
 int /*<<< orphan*/  MOS_UNLOCK (struct mos_softc*) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mos_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mos_reg_read_1 (struct mos_softc*,int /*<<< orphan*/ ) ; 
 int mos_reg_read_2 (struct mos_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_reg_write_1 (struct mos_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mos_reg_write_2 (struct mos_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mos_miibus_readreg(device_t dev, int phy, int reg)
{
	struct mos_softc *sc = device_get_softc(dev);
	uWord val;
	int i, res, locked;

	USETW(val, 0);

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		MOS_LOCK(sc);

	mos_reg_write_2(sc, MOS_PHY_DATA, 0);
	mos_reg_write_1(sc, MOS_PHY_CTL, (phy & MOS_PHYCTL_PHYADDR) |
	    MOS_PHYCTL_READ);
	mos_reg_write_1(sc, MOS_PHY_STS, (reg & MOS_PHYSTS_PHYREG) |
	    MOS_PHYSTS_PENDING);

	for (i = 0; i < MOS_TIMEOUT; i++) {
		if (mos_reg_read_1(sc, MOS_PHY_STS) & MOS_PHYSTS_READY)
			break;
	}
	if (i == MOS_TIMEOUT) {
		MOS_DPRINTFN("MII read timeout");
	}
	res = mos_reg_read_2(sc, MOS_PHY_DATA);

	if (!locked)
		MOS_UNLOCK(sc);
	return (res);
}