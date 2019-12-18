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
 scalar_t__ FWOHCI_STATE_DEAD ; 
 int MAX_OHCI ; 
 int fw_initialized ; 
 int /*<<< orphan*/  fw_probe (int,struct fwohci_softc*) ; 
 struct fwohci_softc* fwinfo ; 

__attribute__((used)) static int
fw_init(void) 
{
	int i, avail;
	struct fwohci_softc *sc;

	if (fw_initialized)
		return (0);

	avail = 0;
	for (i = 0; i < MAX_OHCI; i ++) {
		sc = &fwinfo[i];
		fw_probe(i, sc);
		if (sc->state == FWOHCI_STATE_DEAD)
			break;
		avail ++;
		break;
	}
	fw_initialized = 1;

	return (0);
}