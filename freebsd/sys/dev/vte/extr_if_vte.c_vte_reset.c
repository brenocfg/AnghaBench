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
typedef  int uint16_t ;
struct vte_softc {int /*<<< orphan*/  vte_dev; } ;

/* Variables and functions */
 int CSR_READ_2 (struct vte_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vte_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MCR1_MAC_RESET ; 
 int /*<<< orphan*/  VTE_MACSM ; 
 int /*<<< orphan*/  VTE_MCR1 ; 
 int VTE_RESET_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
vte_reset(struct vte_softc *sc)
{
	uint16_t mcr;
	int i;

	mcr = CSR_READ_2(sc, VTE_MCR1);
	CSR_WRITE_2(sc, VTE_MCR1, mcr | MCR1_MAC_RESET);
	for (i = VTE_RESET_TIMEOUT; i > 0; i--) {
		DELAY(10);
		if ((CSR_READ_2(sc, VTE_MCR1) & MCR1_MAC_RESET) == 0)
			break;
	}
	if (i == 0)
		device_printf(sc->vte_dev, "reset timeout(0x%04x)!\n", mcr);
	/*
	 * Follow the guide of vendor recommended way to reset MAC.
	 * Vendor confirms relying on MCR1_MAC_RESET of VTE_MCR1 is
	 * not reliable so manually reset internal state machine.
	 */
	CSR_WRITE_2(sc, VTE_MACSM, 0x0002);
	CSR_WRITE_2(sc, VTE_MACSM, 0);
	DELAY(5000);
}