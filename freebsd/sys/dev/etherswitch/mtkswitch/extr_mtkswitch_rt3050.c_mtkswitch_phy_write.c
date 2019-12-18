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
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_PCR0 ; 
 int MTKSWITCH_READ (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_UNLOCK (struct mtkswitch_softc*) ; 
 int /*<<< orphan*/  MTKSWITCH_WRITE (struct mtkswitch_softc*,int /*<<< orphan*/ ,int) ; 
 int PCR0_ACTIVE ; 
 int PCR0_DATA (int) ; 
 int PCR0_PHY (int) ; 
 int PCR0_REG (int) ; 
 int PCR0_WRITE ; 
 struct mtkswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtkswitch_phy_write(device_t dev, int phy, int reg, int val)
{
	struct mtkswitch_softc *sc = device_get_softc(dev);

	MTKSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);
	MTKSWITCH_LOCK(sc);
	while (MTKSWITCH_READ(sc, MTKSWITCH_PCR0) & PCR0_ACTIVE);
	MTKSWITCH_WRITE(sc, MTKSWITCH_PCR0, PCR0_WRITE | PCR0_REG(reg) |
	    PCR0_PHY(phy) | PCR0_DATA(val));
	while (MTKSWITCH_READ(sc, MTKSWITCH_PCR0) & PCR0_ACTIVE);
	MTKSWITCH_UNLOCK(sc);
	return (0);
}