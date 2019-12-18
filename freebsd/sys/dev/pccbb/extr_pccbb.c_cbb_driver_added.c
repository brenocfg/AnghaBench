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
struct cbb_softc {int /*<<< orphan*/  intrhand; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_IDENTIFY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DS_NOTPRESENT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
cbb_driver_added(device_t brdev, driver_t *driver)
{
	struct cbb_softc *sc = device_get_softc(brdev);
	device_t *devlist;
	device_t dev;
	int tmp;
	int numdevs;
	int wake = 0;

	DEVICE_IDENTIFY(driver, brdev);
	tmp = device_get_children(brdev, &devlist, &numdevs);
	if (tmp != 0) {
		device_printf(brdev, "Cannot get children list, no reprobe\n");
		return;
	}
	for (tmp = 0; tmp < numdevs; tmp++) {
		dev = devlist[tmp];
		if (device_get_state(dev) == DS_NOTPRESENT &&
		    device_probe_and_attach(dev) == 0)
			wake++;
	}
	free(devlist, M_TEMP);

	if (wake > 0)
		wakeup(&sc->intrhand);
}