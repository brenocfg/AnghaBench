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
struct ure_softc {int sc_phyno; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  URE_LOCK (struct ure_softc*) ; 
 scalar_t__ URE_OCP_BASE_MII ; 
 int /*<<< orphan*/  URE_UNLOCK (struct ure_softc*) ; 
 struct ure_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ure_ocp_reg_write (struct ure_softc*,scalar_t__,int) ; 

__attribute__((used)) static int
ure_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct ure_softc *sc;
	int locked;

	sc = device_get_softc(dev);
	if (sc->sc_phyno != phy)
		return (0);

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		URE_LOCK(sc);
	
	ure_ocp_reg_write(sc, URE_OCP_BASE_MII + reg * 2, val);

	if (!locked)
		URE_UNLOCK(sc);
	return (0);
}