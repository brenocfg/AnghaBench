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
struct imcsmb_pci_softc {int /*<<< orphan*/  semaphore; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct imcsmb_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

void
imcsmb_pci_release_bus(device_t dev)
{
	struct imcsmb_pci_softc *sc;

	sc = device_get_softc(dev);

	/*
	 * IF NEEDED, INSERT MOTHERBOARD-SPECIFIC CODE TO RE-ENABLE DIMM
	 * TEMPERATURE MONITORING HERE.
	 */

	atomic_store_rel_int(&sc->semaphore, 0);
}