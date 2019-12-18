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
struct iwm_softc {int /*<<< orphan*/  fw_dma; int /*<<< orphan*/  sc_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_FH_MEM_TB_MAX_LENGTH ; 
 int iwm_dma_contig_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwm_alloc_fwmem(struct iwm_softc *sc)
{
	/* Must be aligned on a 16-byte boundary. */
	return iwm_dma_contig_alloc(sc->sc_dmat, &sc->fw_dma,
	    IWM_FH_MEM_TB_MAX_LENGTH, 16);
}