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
struct mii_data {int dummy; } ;
struct arswitch_softc {int numphys; int /*<<< orphan*/ * miibus; } ;

/* Variables and functions */
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mii_data *
arswitch_miiforport(struct arswitch_softc *sc, int port)
{
	int phy = port-1;

	if (phy < 0 || phy >= sc->numphys)
		return (NULL);
	return (device_get_softc(sc->miibus[phy]));
}