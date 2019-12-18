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
struct bwi_pci_softc {int /*<<< orphan*/  sc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bwi_resume (int /*<<< orphan*/ *) ; 
 struct bwi_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwi_pci_resume(device_t dev)
{
	struct bwi_pci_softc *psc = device_get_softc(dev);

	bwi_resume(&psc->sc_sc);

	return (0);
}