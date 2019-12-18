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
struct mpr_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct mpr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mpr_free (struct mpr_softc*) ; 
 int /*<<< orphan*/  mpr_pci_free (struct mpr_softc*) ; 

__attribute__((used)) static int
mpr_pci_detach(device_t dev)
{
	struct mpr_softc *sc;
	int error;

	sc = device_get_softc(dev);

	if ((error = mpr_free(sc)) != 0)
		return (error);

	mpr_pci_free(sc);
	return (0);
}