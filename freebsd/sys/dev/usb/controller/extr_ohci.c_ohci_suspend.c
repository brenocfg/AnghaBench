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
typedef  int /*<<< orphan*/  ohci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  ohci_controller_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ohci_dumpregs (int /*<<< orphan*/ *) ; 
 int ohcidebug ; 

__attribute__((used)) static void
ohci_suspend(ohci_softc_t *sc)
{
	DPRINTF("\n");

#ifdef USB_DEBUG
	if (ohcidebug > 2)
		ohci_dumpregs(sc);
#endif

	/* reset HC and leave it suspended */
	ohci_controller_init(sc, 1);
}