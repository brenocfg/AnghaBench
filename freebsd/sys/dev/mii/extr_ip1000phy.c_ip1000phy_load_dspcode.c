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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int,int) ; 

__attribute__((used)) static void
ip1000phy_load_dspcode(struct mii_softc *sc)
{

	PHY_WRITE(sc, 31, 0x0001);
	PHY_WRITE(sc, 27, 0x01e0);
	PHY_WRITE(sc, 31, 0x0002);
	PHY_WRITE(sc, 27, 0xeb8e);
	PHY_WRITE(sc, 31, 0x0000);
	PHY_WRITE(sc, 30, 0x005e);
	PHY_WRITE(sc, 9, 0x0700);

	DELAY(50);
}