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
 int CMD_OK ; 
 scalar_t__ FWOHCI_STATE_ENABLED ; 
 scalar_t__ FWOHCI_STATE_NORMAL ; 
 int /*<<< orphan*/  fw_crom (struct fwohci_softc*) ; 
 int /*<<< orphan*/  fwohci_ibr (struct fwohci_softc*) ; 
 int /*<<< orphan*/  fwohci_poll (struct fwohci_softc*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
fw_busreset(struct fwohci_softc *sc)
{
	int count;

	if (sc->state < FWOHCI_STATE_ENABLED) {
		printf("fwohci not enabled\n");
		return(CMD_OK);
	}
	fw_crom(sc);
	fwohci_ibr(sc);
	count = 0;
	while (sc->state< FWOHCI_STATE_NORMAL) {
		fwohci_poll(sc);
		count ++;
		if (count > 1000) {
			printf("give up to wait bus initialize\n");
			return (-1);
		}
	}
	printf("poll count = %d\n", count);
	return (0);
}