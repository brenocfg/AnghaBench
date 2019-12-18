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
struct mps_softc {int /*<<< orphan*/  mps_dev; } ;

/* Variables and functions */
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mps_alloc_msix(struct mps_softc *sc, int msgs)
{
	int error;

	error = pci_alloc_msix(sc->mps_dev, &msgs);
	return (error);
}