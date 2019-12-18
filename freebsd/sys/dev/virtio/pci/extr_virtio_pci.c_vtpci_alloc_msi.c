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
struct vtpci_softc {int /*<<< orphan*/  vtpci_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtpci_alloc_msi(struct vtpci_softc *sc)
{
	device_t dev;
	int nmsi, cnt, required;

	dev = sc->vtpci_dev;
	required = 1;

	nmsi = pci_msi_count(dev);
	if (nmsi < required)
		return (1);

	cnt = required;
	if (pci_alloc_msi(dev, &cnt) == 0 && cnt >= required)
		return (0);

	pci_release_msi(dev);

	return (1);
}