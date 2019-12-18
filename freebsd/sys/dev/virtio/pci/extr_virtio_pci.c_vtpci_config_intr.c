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
struct vtpci_softc {int /*<<< orphan*/ * vtpci_child_dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONFIG_CHANGE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtpci_config_intr(void *xsc)
{
	struct vtpci_softc *sc;
	device_t child;

	sc = xsc;
	child = sc->vtpci_child_dev;

	if (child != NULL)
		VIRTIO_CONFIG_CHANGE(child);
}