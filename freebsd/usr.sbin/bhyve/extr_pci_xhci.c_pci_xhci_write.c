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
typedef  scalar_t__ uint64_t ;
struct vmctx {int dummy; } ;
struct pci_xhci_softc {scalar_t__ dboff; scalar_t__ rtsoff; scalar_t__ regsend; int /*<<< orphan*/  mtx; } ;
struct pci_devinst {struct pci_xhci_softc* pi_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPRINTF (char*) ; 
 scalar_t__ XHCI_CAPLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pci_xhci_dbregs_write (struct pci_xhci_softc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci_xhci_hostop_write (struct pci_xhci_softc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci_xhci_rtsregs_write (struct pci_xhci_softc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_xhci_write(struct vmctx *ctx, int vcpu, struct pci_devinst *pi,
                int baridx, uint64_t offset, int size, uint64_t value)
{
	struct pci_xhci_softc *sc;

	sc = pi->pi_arg;

	assert(baridx == 0);


	pthread_mutex_lock(&sc->mtx);
	if (offset < XHCI_CAPLEN)	/* read only registers */
		WPRINTF(("pci_xhci: write RO-CAPs offset %ld\r\n", offset));
	else if (offset < sc->dboff)
		pci_xhci_hostop_write(sc, offset, value);
	else if (offset < sc->rtsoff)
		pci_xhci_dbregs_write(sc, offset, value);
	else if (offset < sc->regsend)
		pci_xhci_rtsregs_write(sc, offset, value);
	else
		WPRINTF(("pci_xhci: write invalid offset %ld\r\n", offset));

	pthread_mutex_unlock(&sc->mtx);
}