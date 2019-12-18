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
struct mii_softc {int dummy; } ;

/* Variables and functions */
 int CONFIG_100BASEFX ; 
 int /*<<< orphan*/  MII_LXTPHY_CONFIG ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lxtphy_set_tp(struct mii_softc *sc)
{
	int cfg;

	cfg = PHY_READ(sc, MII_LXTPHY_CONFIG);
	cfg &= ~CONFIG_100BASEFX;
	PHY_WRITE(sc, MII_LXTPHY_CONFIG, cfg);
}