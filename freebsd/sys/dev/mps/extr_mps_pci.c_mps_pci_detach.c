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
struct mps_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct mps_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mps_free (struct mps_softc*) ; 
 int /*<<< orphan*/  mps_pci_free (struct mps_softc*) ; 

__attribute__((used)) static int
mps_pci_detach(device_t dev)
{
	struct mps_softc *sc;
	int error;

	sc = device_get_softc(dev);

	if ((error = mps_free(sc)) != 0)
		return (error);

	mps_pci_free(sc);
	return (0);
}