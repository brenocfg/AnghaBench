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
struct mtkswitch_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_UNLOCK (struct mtkswitch_softc*) ; 
 struct mtkswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtkswitch_phy_write_locked (struct mtkswitch_softc*,int,int,int) ; 

__attribute__((used)) static int
mtkswitch_phy_write(device_t dev, int phy, int reg, int val)
{
	struct mtkswitch_softc *sc = device_get_softc(dev);
	int res;

	if ((phy < 0 || phy >= 32) || (reg < 0 || reg >= 32))
		return (ENXIO);

	MTKSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);
	MTKSWITCH_LOCK(sc);
	res = mtkswitch_phy_write_locked(sc, phy, reg, val);
	MTKSWITCH_UNLOCK(sc);

	return (res);
}