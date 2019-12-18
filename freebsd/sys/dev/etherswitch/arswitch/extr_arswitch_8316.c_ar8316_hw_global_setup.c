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
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8316_GLOBAL_CTRL_MTU_MASK ; 
 int AR8X16_CPU_MIRROR_DIS ; 
 int AR8X16_CPU_PORT_EN ; 
 int AR8X16_FLOOD_MASK_BCAST_TO_CPU ; 
 int AR8X16_MAGIC ; 
 int AR8X16_REG_CPU_PORT ; 
 int AR8X16_REG_FLOOD_MASK ; 
 int /*<<< orphan*/  AR8X16_REG_GLOBAL_CTRL ; 
 int /*<<< orphan*/  AR8X16_REG_SERVICE_TAG ; 
 int AR8X16_REG_TAG_PRIO ; 
 int /*<<< orphan*/  AR8X16_SERVICE_TAG_MASK ; 
 int /*<<< orphan*/  ARSWITCH_LOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  ARSWITCH_UNLOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  arswitch_modifyreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arswitch_writereg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ar8316_hw_global_setup(struct arswitch_softc *sc)
{

	ARSWITCH_LOCK(sc);

	arswitch_writereg(sc->sc_dev, 0x38, AR8X16_MAGIC);

	/* Enable CPU port and disable mirror port. */
	arswitch_writereg(sc->sc_dev, AR8X16_REG_CPU_PORT,
	    AR8X16_CPU_PORT_EN | AR8X16_CPU_MIRROR_DIS);

	/* Setup TAG priority mapping. */
	arswitch_writereg(sc->sc_dev, AR8X16_REG_TAG_PRIO, 0xfa50);

	/*
	 * Flood address table misses to all ports, and enable forwarding of
	 * broadcasts to the cpu port.
	 */
	arswitch_writereg(sc->sc_dev, AR8X16_REG_FLOOD_MASK,
	    AR8X16_FLOOD_MASK_BCAST_TO_CPU | 0x003f003f);

	/* Enable jumbo frames. */
	arswitch_modifyreg(sc->sc_dev, AR8X16_REG_GLOBAL_CTRL,
	    AR8316_GLOBAL_CTRL_MTU_MASK, 9018 + 8 + 2);

	/* Setup service TAG. */
	arswitch_modifyreg(sc->sc_dev, AR8X16_REG_SERVICE_TAG,
	    AR8X16_SERVICE_TAG_MASK, 0);

	ARSWITCH_UNLOCK(sc);
	return (0);
}