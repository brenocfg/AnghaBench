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
struct e6060sw_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  E6060SW_LOCK (struct e6060sw_softc*) ; 
 int /*<<< orphan*/  E6060SW_LOCK_ASSERT (struct e6060sw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E6060SW_UNLOCK (struct e6060sw_softc*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int MDIO_WRITEREG (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct e6060sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
e6060sw_writephy(device_t dev, int phy, int reg, int data)
{
	struct e6060sw_softc *sc;
	int err;

	sc = device_get_softc(dev);
	E6060SW_LOCK_ASSERT(sc, MA_NOTOWNED);

	if (phy < 0 || phy >= 32)
		return (ENXIO);
	if (reg < 0 || reg >= 32)
		return (ENXIO);

	E6060SW_LOCK(sc);
	err = MDIO_WRITEREG(device_get_parent(dev), phy, reg, data);
	E6060SW_UNLOCK(sc);

	return (err);
}