#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcd_conf {int nbytes; int nmajor; int smod; int soff; int ssize; int dsize; scalar_t__ dlast_sga; scalar_t__ slast; scalar_t__ doff; scalar_t__ esg; scalar_t__ dmod; scalar_t__ daddr; int /*<<< orphan*/  saddr; struct sc_pcminfo* ih_user; int /*<<< orphan*/  ih; int /*<<< orphan*/  channel; } ;
struct sc_pcminfo {struct sc_info* sc; } ;
struct sc_info {struct tcd_conf* tcd; TYPE_1__* edma_sc; int /*<<< orphan*/ * res; int /*<<< orphan*/  buf_base_phys; int /*<<< orphan*/  edma_chnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_setup ) (TYPE_1__*,struct tcd_conf*) ;} ;

/* Variables and functions */
 scalar_t__ I2S_TDR0 ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct tcd_conf* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sai_dma_intr ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct tcd_conf*) ; 

__attribute__((used)) static int
setup_dma(struct sc_pcminfo *scp)
{
	struct tcd_conf *tcd;
	struct sc_info *sc;

	sc = scp->sc;

	tcd = malloc(sizeof(struct tcd_conf), M_DEVBUF, M_WAITOK | M_ZERO);
	tcd->channel = sc->edma_chnum;
	tcd->ih = sai_dma_intr;
	tcd->ih_user = scp;
	tcd->saddr = sc->buf_base_phys;
	tcd->daddr = rman_get_start(sc->res[0]) + I2S_TDR0;

	/*
	 * Bytes to transfer per each minor loop.
	 * Hardware FIFO buffer size is 32x32bits.
	 */
	tcd->nbytes = 64;

	tcd->nmajor = 512;
	tcd->smod = 17;	/* dma_size range */
	tcd->dmod = 0;
	tcd->esg = 0;
	tcd->soff = 0x4;
	tcd->doff = 0;
	tcd->ssize = 0x2;
	tcd->dsize = 0x2;
	tcd->slast = 0;
	tcd->dlast_sga = 0;

	sc->tcd = tcd;

	sc->edma_sc->dma_setup(sc->edma_sc, sc->tcd);

	return (0);
}