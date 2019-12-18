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
struct nfe_softc {scalar_t__ nfe_msix; int /*<<< orphan*/  nfe_intrs; int /*<<< orphan*/  nfe_irq_mask; } ;

/* Variables and functions */
 scalar_t__ NFE_READ (struct nfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
nfe_enable_intr(struct nfe_softc *sc)
{

	if (sc->nfe_msix != 0) {
		/* XXX Should have a better way to enable interrupts! */
		if (NFE_READ(sc, sc->nfe_irq_mask) == 0)
			NFE_WRITE(sc, sc->nfe_irq_mask, sc->nfe_intrs);
	} else
		NFE_WRITE(sc, sc->nfe_irq_mask, sc->nfe_intrs);
}