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
typedef  scalar_t__ uint32_t ;
struct pci_mv_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  MV_INT_CAUSE1 ; 
 int /*<<< orphan*/  MV_INT_CAUSE2 ; 
 scalar_t__ pci_dw_dbi_rd4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dw_dbi_wr4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pci_mv_intr(void *arg)
{
	struct pci_mv_softc *sc = arg;
	uint32_t cause1, cause2;

	/* Ack all interrups */
	cause1 = pci_dw_dbi_rd4(sc->dev, MV_INT_CAUSE1);
	cause2 = pci_dw_dbi_rd4(sc->dev, MV_INT_CAUSE2);
	if (cause1 == 0 || cause2 == 0)
		return(FILTER_STRAY);

	pci_dw_dbi_wr4(sc->dev, MV_INT_CAUSE1, cause1);
	pci_dw_dbi_wr4(sc->dev, MV_INT_CAUSE2, cause2);
	return (FILTER_HANDLED);
}