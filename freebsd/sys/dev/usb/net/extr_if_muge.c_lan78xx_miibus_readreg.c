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
struct muge_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MII_ACC ; 
 int ETH_MII_ACC_MII_BUSY_ ; 
 int ETH_MII_ACC_MII_READ_ ; 
 int /*<<< orphan*/  ETH_MII_DATA ; 
 int /*<<< orphan*/  MUGE_LOCK (struct muge_softc*) ; 
 int /*<<< orphan*/  MUGE_UNLOCK (struct muge_softc*) ; 
 struct muge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan78xx_read_reg (struct muge_softc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ lan78xx_wait_for_bits (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lan78xx_write_reg (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int le32toh (int) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  muge_warn_printf (struct muge_softc*,char*) ; 

__attribute__((used)) static int
lan78xx_miibus_readreg(device_t dev, int phy, int reg) {

	struct muge_softc *sc = device_get_softc(dev);
	int locked;
	uint32_t addr, val;

	val = 0;
	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		MUGE_LOCK(sc);

	if (lan78xx_wait_for_bits(sc, ETH_MII_ACC, ETH_MII_ACC_MII_BUSY_) !=
	    0) {
		muge_warn_printf(sc, "MII is busy\n");
		goto done;
	}

	addr = (phy << 11) | (reg << 6) |
	    ETH_MII_ACC_MII_READ_ | ETH_MII_ACC_MII_BUSY_;
	lan78xx_write_reg(sc, ETH_MII_ACC, addr);

	if (lan78xx_wait_for_bits(sc, ETH_MII_ACC, ETH_MII_ACC_MII_BUSY_) !=
	    0) {
		muge_warn_printf(sc, "MII read timeout\n");
		goto done;
	}

	lan78xx_read_reg(sc, ETH_MII_DATA, &val);
	val = le32toh(val);

done:
	if (!locked)
		MUGE_UNLOCK(sc);

	return (val & 0xFFFF);
}