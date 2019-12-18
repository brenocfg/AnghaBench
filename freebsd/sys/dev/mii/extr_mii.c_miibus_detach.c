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
struct mii_data {int /*<<< orphan*/ * mii_ifp; int /*<<< orphan*/  mii_media; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
miibus_detach(device_t dev)
{
	struct mii_data		*mii;

	bus_generic_detach(dev);
	mii = device_get_softc(dev);
	ifmedia_removeall(&mii->mii_media);
	mii->mii_ifp = NULL;

	return (0);
}