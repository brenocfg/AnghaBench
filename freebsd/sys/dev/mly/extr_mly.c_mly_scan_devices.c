#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mly_softc {int mly_cam_channels; TYPE_1__** mly_btl; } ;
struct TYPE_2__ {int /*<<< orphan*/  mb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLY_BTL_RESCAN ; 
 scalar_t__ MLY_BUS_IS_VALID (struct mly_softc*,int) ; 
 int MLY_MAX_TARGETS ; 
 int /*<<< orphan*/  bzero (TYPE_1__***,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
mly_scan_devices(struct mly_softc *sc)
{
    int		bus, target;

    debug_called(1);

    /*
     * Clear any previous BTL information.
     */
    bzero(&sc->mly_btl, sizeof(sc->mly_btl));

    /*
     * Mark all devices as requiring a rescan, and let the next
     * periodic scan collect them. 
     */
    for (bus = 0; bus < sc->mly_cam_channels; bus++)
	if (MLY_BUS_IS_VALID(sc, bus)) 
	    for (target = 0; target < MLY_MAX_TARGETS; target++)
		sc->mly_btl[bus][target].mb_flags = MLY_BTL_RESCAN;

}