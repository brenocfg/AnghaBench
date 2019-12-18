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
struct TYPE_2__ {int /*<<< orphan*/  mii_dev; } ;
struct mlphy_softc {scalar_t__ ml_dev; TYPE_1__ ml_mii; } ;
struct mii_softc {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,scalar_t__**,int*) ; 
 struct mii_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mii_softc *
mlphy_find_other(struct mlphy_softc *msc)
{
	device_t		*devlist;
	struct mii_softc *retval;
	int i, devs;

	retval = NULL;
	if (device_get_children(msc->ml_mii.mii_dev, &devlist, &devs) != 0)
		return (NULL);
	for (i = 0; i < devs; i++) {
		if (devlist[i] != msc->ml_dev) {
			retval = device_get_softc(devlist[i]);
			break;
		}
	}
	free(devlist, M_TEMP);
	return (retval);
}