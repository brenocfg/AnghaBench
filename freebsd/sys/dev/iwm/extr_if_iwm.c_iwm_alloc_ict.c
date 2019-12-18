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
struct iwm_softc {int /*<<< orphan*/  ict_dma; int /*<<< orphan*/  sc_dmat; } ;

/* Variables and functions */
 int IWM_ICT_PADDR_SHIFT ; 
 int /*<<< orphan*/  IWM_ICT_SIZE ; 
 int iwm_dma_contig_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwm_alloc_ict(struct iwm_softc *sc)
{
	return iwm_dma_contig_alloc(sc->sc_dmat, &sc->ict_dma,
	    IWM_ICT_SIZE, 1<<IWM_ICT_PADDR_SHIFT);
}