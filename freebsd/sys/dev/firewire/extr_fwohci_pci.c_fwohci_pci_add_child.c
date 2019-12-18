#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/ * bdev; } ;
struct fwohci_softc {TYPE_1__ fc; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fwohci_pci_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwohci_poll (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static device_t
fwohci_pci_add_child(device_t dev, u_int order, const char *name, int unit)
{
	struct fwohci_softc *sc;
	device_t child;
	int err = 0;

	sc = (struct fwohci_softc *)device_get_softc(dev);
	child = device_add_child(dev, name, unit);
	if (child == NULL)
		return (child);

	sc->fc.bdev = child;
	device_set_ivars(child, &sc->fc);

	err = device_probe_and_attach(child);
	if (err) {
		device_printf(dev, "probe_and_attach failed with err=%d\n",
		    err);
		fwohci_pci_detach(dev);
		device_delete_child(dev, child);
		return NULL;
	}

	/* XXX
	 * Clear the bus reset event flag to start transactions even when
	 * interrupt is disabled during the boot process.
	 */
	if (cold) {
		int s;
		DELAY(250); /* 2 cycles */
		s = splfw();
		fwohci_poll(&sc->fc, 0, -1);
		splx(s);
	}

	return (child);
}