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
struct chipc_softc {scalar_t__ dev; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPC_QUIRK (struct chipc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  MUX_SPROM ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ bhnd_bus_find_hostb_device (scalar_t__) ; 
 int device_get_children (scalar_t__,scalar_t__**,int*) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  device_is_attached (scalar_t__) ; 
 scalar_t__ device_is_suspended (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
chipc_should_enable_muxed_sprom(struct chipc_softc *sc)
{
	device_t	*devs;
	device_t	 hostb;
	device_t	 parent;
	int		 devcount;
	int		 error;
	bool		 result;

	/* Nothing to do? */
	if (!CHIPC_QUIRK(sc, MUX_SPROM))
		return (true);

	mtx_lock(&Giant);	/* for newbus */

	parent = device_get_parent(sc->dev);
	hostb = bhnd_bus_find_hostb_device(parent);

	if ((error = device_get_children(parent, &devs, &devcount))) {
		mtx_unlock(&Giant);
		return (false);
	}

	/* Reject any active devices other than ChipCommon, or the
	 * host bridge (if any). */
	result = true;
	for (int i = 0; i < devcount; i++) {
		if (devs[i] == hostb || devs[i] == sc->dev)
			continue;

		if (!device_is_attached(devs[i]))
			continue;

		if (device_is_suspended(devs[i]))
			continue;

		/* Active device; assume SPROM is busy */
		result = false;
		break;
	}

	free(devs, M_TEMP);
	mtx_unlock(&Giant);
	return (result);
}