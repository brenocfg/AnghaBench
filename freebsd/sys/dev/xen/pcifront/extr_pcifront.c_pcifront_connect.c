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
struct pcifront_device {int /*<<< orphan*/  ndev; TYPE_1__* xdev; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  devclass_t ;
struct TYPE_2__ {char* nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  WPRINTF (char*,...) ; 
 int /*<<< orphan*/  XenbusStateConnected ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct pcifront_device*) ; 
 int /*<<< orphan*/  get_pdev (struct pcifront_device*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  xenbus_switch_state (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcifront_connect(struct pcifront_device *pdev)
{
	device_t nexus;
	devclass_t nexus_devclass;

	/* We will add our device as a child of the nexus0 device */
	if (!(nexus_devclass = devclass_find("nexus")) ||
		!(nexus = devclass_get_device(nexus_devclass, 0))) {
		WPRINTF("could not find nexus0!\n");
		return -1;
	}

	/* Create a newbus device representing this frontend instance */
	pdev->ndev = BUS_ADD_CHILD(nexus, 0, "xpcife", pdev->unit);
	if (!pdev->ndev) {
		WPRINTF("could not create xpcife%d!\n", pdev->unit);
		return -EFAULT;
	}
	get_pdev(pdev);
	device_set_ivars(pdev->ndev, pdev);

	/* Good to go connected now */
	xenbus_switch_state(pdev->xdev, NULL, XenbusStateConnected);

	printf("pcifront: connected to %s\n", pdev->xdev->nodename);

	mtx_lock(&Giant);
	device_probe_and_attach(pdev->ndev);
	mtx_unlock(&Giant);

	return 0;
}