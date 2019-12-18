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
typedef  int /*<<< orphan*/  uint32_t ;
struct mii_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_KSZPHY_EXTREG ; 
 int /*<<< orphan*/  MII_KSZPHY_EXTREG_READ ; 
 int /*<<< orphan*/  PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
ksz9021_read(struct mii_softc *sc, uint32_t reg)
{

	PHY_WRITE(sc, MII_KSZPHY_EXTREG, reg);

	return (PHY_READ(sc, MII_KSZPHY_EXTREG_READ));
}