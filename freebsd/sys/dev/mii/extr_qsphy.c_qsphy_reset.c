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
 int /*<<< orphan*/  MII_QSPHY_IMASK ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_phy_reset (struct mii_softc*) ; 

__attribute__((used)) static void
qsphy_reset(struct mii_softc *sc)
{

	mii_phy_reset(sc);
	PHY_WRITE(sc, MII_QSPHY_IMASK, 0);
}