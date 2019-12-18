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
struct smsc_softc {int sc_phyno; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMSC_LOCK (struct smsc_softc*) ; 
 int /*<<< orphan*/  SMSC_MII_ADDR ; 
 int SMSC_MII_BUSY ; 
 int /*<<< orphan*/  SMSC_MII_DATA ; 
 int SMSC_MII_WRITE ; 
 int /*<<< orphan*/  SMSC_UNLOCK (struct smsc_softc*) ; 
 struct smsc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int htole32 (int) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 scalar_t__ smsc_wait_for_bits (struct smsc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc_warn_printf (struct smsc_softc*,char*) ; 
 int /*<<< orphan*/  smsc_write_reg (struct smsc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
smsc_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct smsc_softc *sc = device_get_softc(dev);
	int locked;
	uint32_t addr;

	if (sc->sc_phyno != phy)
		return (0);

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		SMSC_LOCK(sc);

	if (smsc_wait_for_bits(sc, SMSC_MII_ADDR, SMSC_MII_BUSY) != 0) {
		smsc_warn_printf(sc, "MII is busy\n");
		goto done;
	}

	val = htole32(val);
	smsc_write_reg(sc, SMSC_MII_DATA, val);

	addr = (phy << 11) | (reg << 6) | SMSC_MII_WRITE | SMSC_MII_BUSY;
	smsc_write_reg(sc, SMSC_MII_ADDR, addr);

	if (smsc_wait_for_bits(sc, SMSC_MII_ADDR, SMSC_MII_BUSY) != 0)
		smsc_warn_printf(sc, "MII write timeout\n");

done:
	if (!locked)
		SMSC_UNLOCK(sc);
	return (0);
}