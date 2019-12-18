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
struct stge_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  STGE_MII_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_MII_UNLOCK (struct stge_softc*) ; 
 struct stge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_bitbang_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  stge_mii_bitbang_ops ; 

__attribute__((used)) static int
stge_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct stge_softc *sc;

	sc = device_get_softc(dev);

	STGE_MII_LOCK(sc);
	mii_bitbang_writereg(dev, &stge_mii_bitbang_ops, phy, reg, val);
	STGE_MII_UNLOCK(sc);
	return (0);
}