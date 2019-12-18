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
struct xhci_trb {scalar_t__ qwTrb0; int /*<<< orphan*/  dwTrb3; int /*<<< orphan*/  dwTrb2; } ;
struct xhci_softc {scalar_t__ sc_cmd_addr; int /*<<< orphan*/  sc_cmd_cv; int /*<<< orphan*/ * sc_cmd_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xhci_check_command(struct xhci_softc *sc, struct xhci_trb *trb)
{
	if (sc->sc_cmd_addr == trb->qwTrb0) {
		DPRINTF("Received command event\n");
		sc->sc_cmd_result[0] = trb->dwTrb2;
		sc->sc_cmd_result[1] = trb->dwTrb3;
		cv_signal(&sc->sc_cmd_cv);
		return (1);	/* command match */
	}
	return (0);
}