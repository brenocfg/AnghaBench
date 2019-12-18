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
 int EWOULDBLOCK ; 
 scalar_t__ atomic_cmpset_acq_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct imcsmb_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
imcsmb_pci_request_bus(device_t dev)
{
	struct imcsmb_pci_softc *sc;
	int rc;

	sc = device_get_softc(dev);
	rc = 0;

	/* We don't want to block. Use a simple test-and-set semaphore to
	 * protect the bus.
	 */
	if (atomic_cmpset_acq_int(&sc->semaphore, 0, 1) == 0) {
		rc = EWOULDBLOCK;
	}

	/*
	 * IF NEEDED, INSERT MOTHERBOARD-SPECIFIC CODE TO DISABLE DIMM
	 * TEMPERATURE MONITORING HERE.
	 */

	return (rc);
}