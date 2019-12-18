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
struct tcd_conf {int channel; int smod; int dmod; int ssize; int dsize; int soff; int doff; int nmajor; int majorelink; int majorelinkch; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dlast_sga; int /*<<< orphan*/  slast; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  ih_user; int /*<<< orphan*/  ih; } ;
struct edma_softc {int dummy; } ;
struct edma_channel {int /*<<< orphan*/  ih_user; int /*<<< orphan*/  ih; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_EEI ; 
 int /*<<< orphan*/  DMA_ERQ ; 
 int /*<<< orphan*/  DMA_TCDn_ATTR (int) ; 
 int /*<<< orphan*/  DMA_TCDn_BITER_ELINKNO (int) ; 
 int /*<<< orphan*/  DMA_TCDn_CITER_ELINKNO (int) ; 
 int /*<<< orphan*/  DMA_TCDn_CSR (int) ; 
 int /*<<< orphan*/  DMA_TCDn_DADDR (int) ; 
 int /*<<< orphan*/  DMA_TCDn_DLASTSGA (int) ; 
 int /*<<< orphan*/  DMA_TCDn_DOFF (int) ; 
 int /*<<< orphan*/  DMA_TCDn_NBYTES_MLOFFYES (int) ; 
 int /*<<< orphan*/  DMA_TCDn_SADDR (int) ; 
 int /*<<< orphan*/  DMA_TCDn_SLAST (int) ; 
 int /*<<< orphan*/  DMA_TCDn_SOFF (int) ; 
 int READ4 (struct edma_softc*,int /*<<< orphan*/ ) ; 
 int TCD_ATTR_DMOD_SHIFT ; 
 int TCD_ATTR_DSIZE_SHIFT ; 
 int TCD_ATTR_SMOD_SHIFT ; 
 int TCD_ATTR_SSIZE_SHIFT ; 
 int TCD_CSR_INTMAJOR ; 
 int TCD_CSR_MAJORELINK ; 
 int TCD_CSR_MAJORELINKCH_SHIFT ; 
 int /*<<< orphan*/  TCD_WRITE2 (struct edma_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCD_WRITE4 (struct edma_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct edma_softc*,int /*<<< orphan*/ ,int) ; 
 struct edma_channel* edma_map ; 

__attribute__((used)) static int
dma_setup(struct edma_softc *sc, struct tcd_conf *tcd)
{
	struct edma_channel *ch;
	int chnum;
	int reg;

	chnum = tcd->channel;

	ch = &edma_map[chnum];
	ch->ih = tcd->ih;
	ch->ih_user = tcd->ih_user;

	TCD_WRITE4(sc, DMA_TCDn_SADDR(chnum), tcd->saddr);
	TCD_WRITE4(sc, DMA_TCDn_DADDR(chnum), tcd->daddr);

	reg = (tcd->smod << TCD_ATTR_SMOD_SHIFT);
	reg |= (tcd->dmod << TCD_ATTR_DMOD_SHIFT);
	reg |= (tcd->ssize << TCD_ATTR_SSIZE_SHIFT);
	reg |= (tcd->dsize << TCD_ATTR_DSIZE_SHIFT);
	TCD_WRITE2(sc, DMA_TCDn_ATTR(chnum), reg);

	TCD_WRITE2(sc, DMA_TCDn_SOFF(chnum), tcd->soff);
	TCD_WRITE2(sc, DMA_TCDn_DOFF(chnum), tcd->doff);
	TCD_WRITE4(sc, DMA_TCDn_SLAST(chnum), tcd->slast);
	TCD_WRITE4(sc, DMA_TCDn_DLASTSGA(chnum), tcd->dlast_sga);
	TCD_WRITE4(sc, DMA_TCDn_NBYTES_MLOFFYES(chnum), tcd->nbytes);

	reg = tcd->nmajor; /* Current Major Iteration Count */
	TCD_WRITE2(sc, DMA_TCDn_CITER_ELINKNO(chnum), reg);
	TCD_WRITE2(sc, DMA_TCDn_BITER_ELINKNO(chnum), reg);

	reg = (TCD_CSR_INTMAJOR);
	if(tcd->majorelink == 1) {
		reg |= TCD_CSR_MAJORELINK;
		reg |= (tcd->majorelinkch << TCD_CSR_MAJORELINKCH_SHIFT);
	}
	TCD_WRITE2(sc, DMA_TCDn_CSR(chnum), reg);

	/* Enable requests */
	reg = READ4(sc, DMA_ERQ);
	reg |= (0x1 << chnum);
	WRITE4(sc, DMA_ERQ, reg);

	/* Enable error interrupts */
	reg = READ4(sc, DMA_EEI);
	reg |= (0x1 << chnum);
	WRITE4(sc, DMA_EEI, reg);

	return (0);
}