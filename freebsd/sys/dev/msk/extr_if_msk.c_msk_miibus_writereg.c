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
struct msk_if_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct msk_if_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int msk_phy_writereg (struct msk_if_softc*,int,int,int) ; 

__attribute__((used)) static int
msk_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct msk_if_softc *sc_if;

	sc_if = device_get_softc(dev);

	return (msk_phy_writereg(sc_if, phy, reg, val));
}