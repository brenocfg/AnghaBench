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
struct cbb_softc {int /*<<< orphan*/  bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int cbb_detach (int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_free_secbus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cbb_pci_detach(device_t brdev)
{
#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	struct cbb_softc *sc = device_get_softc(brdev);
#endif
	int error;

	error = cbb_detach(brdev);
#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	if (error == 0)
		pcib_free_secbus(brdev, &sc->bus);
#endif
	return (error);
}