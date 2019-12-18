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
struct fwohci_softc {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ FWOHCI_STATE_ENABLED ; 
 int MAX_OHCI ; 
 scalar_t__ fw_initialized ; 
 struct fwohci_softc* fwinfo ; 
 int /*<<< orphan*/  fwohci_poll (struct fwohci_softc*) ; 

void
fw_poll(void)
{
	struct fwohci_softc *sc;
	int i;

	if (fw_initialized == 0)
		return;

	for (i = 0; i < MAX_OHCI; i ++) {
		sc = &fwinfo[i];
		if (sc->state < FWOHCI_STATE_ENABLED)
			break;
		fwohci_poll(sc);
	}
}