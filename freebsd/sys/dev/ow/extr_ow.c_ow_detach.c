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
struct ow_softc {int dummy; } ;
struct ow_devinfo {int dummy; } ;
typedef  struct ow_devinfo device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_OW ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  OW_LOCK_DESTROY (struct ow_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (struct ow_devinfo) ; 
 int /*<<< orphan*/  device_delete_child (struct ow_devinfo,struct ow_devinfo) ; 
 scalar_t__ device_get_children (struct ow_devinfo,struct ow_devinfo**,int*) ; 
 struct ow_devinfo* device_get_ivars (struct ow_devinfo) ; 
 struct ow_softc* device_get_softc (struct ow_devinfo) ; 
 int /*<<< orphan*/  free (struct ow_devinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ow_detach(device_t ndev)
{
	device_t *children, child;
	int nkid, i;
	struct ow_devinfo *di;
	struct ow_softc *sc;

	sc = device_get_softc(ndev);
	/*
	 * detach all the children first. This is blocking until any threads
	 * have stopped, etc.
	 */
	bus_generic_detach(ndev);

	/*
	 * We delete all the children, and free up the ivars 
	 */
	if (device_get_children(ndev, &children, &nkid) != 0)
		return ENOMEM;
	for (i = 0; i < nkid; i++) {
		child = children[i];
		di = device_get_ivars(child);
		free(di, M_OW);
		device_delete_child(ndev, child);
	}
	free(children, M_TEMP);

	OW_LOCK_DESTROY(sc);
	return 0;
}