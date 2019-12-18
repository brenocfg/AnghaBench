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
typedef  int uint32_t ;
struct ehci_softc {int dummy; } ;

/* Variables and functions */
 int EHCI_CMD_IAAD ; 
 int /*<<< orphan*/  EHCI_USBCMD ; 
 int EOREAD4 (struct ehci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOWRITE4 (struct ehci_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ehci_doorbell_async(struct ehci_softc *sc)
{
	uint32_t temp;

	/*
	 * XXX Performance quirk: Some Host Controllers have a too low
	 * interrupt rate. Issue an IAAD to stimulate the Host
	 * Controller after queueing the BULK transfer.
	 *
	 * XXX Force the host controller to refresh any QH caches.
	 */
	temp = EOREAD4(sc, EHCI_USBCMD);
	if (!(temp & EHCI_CMD_IAAD))
		EOWRITE4(sc, EHCI_USBCMD, temp | EHCI_CMD_IAAD);
}