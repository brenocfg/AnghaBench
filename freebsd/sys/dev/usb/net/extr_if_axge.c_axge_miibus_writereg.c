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
struct axge_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_ACCESS_PHY ; 
 int /*<<< orphan*/  AXGE_LOCK (struct axge_softc*) ; 
 int /*<<< orphan*/  AXGE_UNLOCK (struct axge_softc*) ; 
 int /*<<< orphan*/  axge_write_cmd_2 (struct axge_softc*,int /*<<< orphan*/ ,int,int,int) ; 
 struct axge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
axge_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct axge_softc *sc;
	int locked;

	sc = device_get_softc(dev);
	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		AXGE_LOCK(sc);

	axge_write_cmd_2(sc, AXGE_ACCESS_PHY, reg, phy, val);

	if (!locked)
		AXGE_UNLOCK(sc);

	return (0);
}