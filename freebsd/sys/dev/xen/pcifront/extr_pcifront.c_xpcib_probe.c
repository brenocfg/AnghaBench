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
struct xpcib_softc {struct pcifront_device* pdev; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; } ;
struct pcifront_device {TYPE_1__* xdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  otherend_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xpcib_probe(device_t dev)
{
	struct xpcib_softc *sc = (struct xpcib_softc *)device_get_softc(dev);
	struct pcifront_device *pdev = (struct pcifront_device *)device_get_ivars(device_get_parent(dev));

	DPRINTF("xpcib probe (bus=%d)\n", device_get_unit(dev));

	sc->domain = pdev->xdev->otherend_id;
	sc->bus = device_get_unit(dev);
	sc->pdev = pdev;
	
	return 0;
}