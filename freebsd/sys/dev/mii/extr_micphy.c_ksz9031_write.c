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
typedef  int uint32_t ;
struct mii_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_KSZ9031_MMD_ACCESS_CTRL ; 
 int /*<<< orphan*/  MII_KSZ9031_MMD_ACCESS_DATA ; 
 int MII_KSZ9031_MMD_DATA_NOINC ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ksz9031_write(struct mii_softc *sc, uint32_t devaddr, uint32_t reg,
	uint32_t val)
{

	/* Set up device address and register. */
	PHY_WRITE(sc, MII_KSZ9031_MMD_ACCESS_CTRL, devaddr);
	PHY_WRITE(sc, MII_KSZ9031_MMD_ACCESS_DATA, reg);

	/* Select register data for MMD and write the value. */
	PHY_WRITE(sc, MII_KSZ9031_MMD_ACCESS_CTRL,
	    MII_KSZ9031_MMD_DATA_NOINC | devaddr);
	PHY_WRITE(sc, MII_KSZ9031_MMD_ACCESS_DATA, val);
}