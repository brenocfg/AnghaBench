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
struct ukswitch_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int MDIO_READREG (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UKSWITCH_LOCK (struct ukswitch_softc*) ; 
 int /*<<< orphan*/  UKSWITCH_LOCK_ASSERT (struct ukswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UKSWITCH_UNLOCK (struct ukswitch_softc*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ukswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ukswitch_readphy(device_t dev, int phy, int reg)
{
	struct ukswitch_softc *sc;
	int data;

	sc = device_get_softc(dev);
	UKSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);

	if (phy < 0 || phy >= 32)
		return (ENXIO);
	if (reg < 0 || reg >= 32)
		return (ENXIO);

	UKSWITCH_LOCK(sc);
	data = MDIO_READREG(device_get_parent(dev), phy, reg);
	UKSWITCH_UNLOCK(sc);

	return (data);
}