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
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int LINK_STATE_DOWN ; 
 int LINK_STATE_UNKNOWN ; 
 int LINK_STATE_UP ; 
 int /*<<< orphan*/  MIIBUS_LINKCHG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
miibus_linkchg(device_t dev)
{
	struct mii_data		*mii;
	device_t		parent;
	int			link_state;

	parent = device_get_parent(dev);
	MIIBUS_LINKCHG(parent);

	mii = device_get_softc(dev);

	if (mii->mii_media_status & IFM_AVALID) {
		if (mii->mii_media_status & IFM_ACTIVE)
			link_state = LINK_STATE_UP;
		else
			link_state = LINK_STATE_DOWN;
	} else
		link_state = LINK_STATE_UNKNOWN;
	if_link_state_change(mii->mii_ifp, link_state);
}