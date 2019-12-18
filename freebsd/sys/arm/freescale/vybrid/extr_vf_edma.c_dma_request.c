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
struct edma_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TCDn_CSR (int) ; 
 int TCD_CSR_START ; 
 int TCD_READ2 (struct edma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCD_WRITE2 (struct edma_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dma_request(struct edma_softc *sc, int chnum)
{
	int reg;

	/* Start */
	reg = TCD_READ2(sc, DMA_TCDn_CSR(chnum));
	reg |= TCD_CSR_START;
	TCD_WRITE2(sc, DMA_TCDn_CSR(chnum), reg);

	return (0);
}