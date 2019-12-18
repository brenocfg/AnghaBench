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
struct ccp_softc {int /*<<< orphan*/  queues; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccp_hw_detach_queue (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ccp_release_interrupts (struct ccp_softc*) ; 
 int /*<<< orphan*/  ccp_unmap_pci_bar (int /*<<< orphan*/ ) ; 
 struct ccp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 

void
ccp_hw_detach(device_t dev)
{
	struct ccp_softc *sc;
	unsigned i;

	sc = device_get_softc(dev);

	for (i = 0; i < nitems(sc->queues); i++)
		ccp_hw_detach_queue(dev, i);

	ccp_release_interrupts(sc);
	pci_disable_busmaster(dev);
	ccp_unmap_pci_bar(dev);
}