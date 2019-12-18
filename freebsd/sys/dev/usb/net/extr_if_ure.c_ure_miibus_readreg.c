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
typedef  int uint16_t ;
struct ure_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int URE_GMEDIASTAT ; 
 int /*<<< orphan*/  URE_LOCK (struct ure_softc*) ; 
 int /*<<< orphan*/  URE_MCU_TYPE_PLA ; 
 scalar_t__ URE_OCP_BASE_MII ; 
 int /*<<< orphan*/  URE_UNLOCK (struct ure_softc*) ; 
 struct ure_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int ure_ocp_reg_read (struct ure_softc*,scalar_t__) ; 
 int ure_read_1 (struct ure_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ure_miibus_readreg(device_t dev, int phy, int reg)
{
	struct ure_softc *sc;
	uint16_t val;
	int locked;

	sc = device_get_softc(dev);
	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		URE_LOCK(sc);

	/* Let the rgephy driver read the URE_GMEDIASTAT register. */
	if (reg == URE_GMEDIASTAT) {
		if (!locked)
			URE_UNLOCK(sc);
		return (ure_read_1(sc, URE_GMEDIASTAT, URE_MCU_TYPE_PLA));
	}

	val = ure_ocp_reg_read(sc, URE_OCP_BASE_MII + reg * 2);

	if (!locked)
		URE_UNLOCK(sc);
	return (val);
}