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
struct mii_softc {int /*<<< orphan*/ * mii_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct mii_softc*,int /*<<< orphan*/ ) ; 
 struct mii_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_list ; 

int
mii_phy_detach(device_t dev)
{
	struct mii_softc *sc;

	sc = device_get_softc(dev);
	sc->mii_dev = NULL;
	LIST_REMOVE(sc, mii_list);
	return (0);
}