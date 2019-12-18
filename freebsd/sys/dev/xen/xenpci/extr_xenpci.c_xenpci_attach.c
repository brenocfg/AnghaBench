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
struct xenpci_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct xenpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int xenpci_allocate_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenpci_deallocate_resources (int /*<<< orphan*/ ) ; 
 int xenpci_irq_init (int /*<<< orphan*/ ,struct xenpci_softc*) ; 

__attribute__((used)) static int
xenpci_attach(device_t dev)
{
	struct xenpci_softc *scp = device_get_softc(dev);
	int error;

	error = xenpci_allocate_resources(dev);
	if (error) {
		device_printf(dev, "xenpci_allocate_resources failed(%d).\n",
		    error);
		goto errexit;
	}

	/*
	 * Hook the irq up to evtchn
	 */
	error = xenpci_irq_init(dev, scp);
	if (error) {
		device_printf(dev, "xenpci_irq_init failed(%d).\n",
			error);
		goto errexit;
	}

	return (0);

errexit:
	/*
	 * Undo anything we may have done.
	 */
	xenpci_deallocate_resources(dev);
	return (error);
}