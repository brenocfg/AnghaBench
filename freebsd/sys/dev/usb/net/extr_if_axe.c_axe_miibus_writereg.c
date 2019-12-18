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
struct axe_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXE_CMD_MII_OPMODE_HW ; 
 int /*<<< orphan*/  AXE_CMD_MII_OPMODE_SW ; 
 int /*<<< orphan*/  AXE_CMD_MII_WRITE_REG ; 
 int /*<<< orphan*/  AXE_LOCK (struct axe_softc*) ; 
 int /*<<< orphan*/  AXE_UNLOCK (struct axe_softc*) ; 
 int /*<<< orphan*/  axe_cmd (struct axe_softc*,int /*<<< orphan*/ ,int,int,int*) ; 
 struct axe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int htole32 (int) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
axe_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct axe_softc *sc = device_get_softc(dev);
	int locked;

	val = htole32(val);
	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		AXE_LOCK(sc);

	axe_cmd(sc, AXE_CMD_MII_OPMODE_SW, 0, 0, NULL);
	axe_cmd(sc, AXE_CMD_MII_WRITE_REG, reg, phy, &val);
	axe_cmd(sc, AXE_CMD_MII_OPMODE_HW, 0, 0, NULL);

	if (!locked)
		AXE_UNLOCK(sc);
	return (0);
}