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
typedef  int /*<<< orphan*/  uint32_t ;
struct cbb_softc {int /*<<< orphan*/  intrhand; int /*<<< orphan*/  (* chipinit ) (struct cbb_softc*) ;} ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CBB_SOCKET_EVENT ; 
 int /*<<< orphan*/  CBB_SOCKET_MASK ; 
 int /*<<< orphan*/  CBB_SOCKET_MASK_CD ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_get (struct cbb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_set (struct cbb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_setb (struct cbb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cbb_softc*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cbb_pci_resume(device_t brdev)
{
	int	error = 0;
	struct cbb_softc *sc = (struct cbb_softc *)device_get_softc(brdev);
	uint32_t tmp;

	/*
	 * In the APM and early ACPI era, BIOSes saved the PCI config
	 * registers. As chips became more complicated, that functionality moved
	 * into the ACPI code / tables. We must therefore, restore the settings
	 * we made here to make sure the device come back. Transitions to Dx
	 * from D0 and back to D0 cause the bridge to lose its config space, so
	 * all the bus mappings and such are preserved.
	 *
	 * The PCI layer handles standard PCI registers like the
	 * command register and BARs, but cbb-specific registers are
	 * handled here.
	 */
	sc->chipinit(sc);

	/* reset interrupt -- Do we really need to do this? */
	tmp = cbb_get(sc, CBB_SOCKET_EVENT);
	cbb_set(sc, CBB_SOCKET_EVENT, tmp);

	/* CSC Interrupt: Card detect interrupt on */
	cbb_setb(sc, CBB_SOCKET_MASK, CBB_SOCKET_MASK_CD);

	/* Signal the thread to wakeup. */
	wakeup(&sc->intrhand);

	error = bus_generic_resume(brdev);

	return (error);
}