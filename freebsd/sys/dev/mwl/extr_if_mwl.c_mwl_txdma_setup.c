#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct mwl_txdesc* dd_desc; struct mwl_txbuf* dd_bufptr; } ;
struct mwl_txq {TYPE_1__ dma; } ;
struct mwl_txdesc {int dummy; } ;
struct mwl_txbuf {int /*<<< orphan*/  bf_dmamap; int /*<<< orphan*/  bf_daddr; struct mwl_txdesc* bf_desc; } ;
struct mwl_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  DS2PHYS (TYPE_1__*,struct mwl_txdesc*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MWL_TXDESC ; 
 int /*<<< orphan*/  M_MWLDEV ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 struct mwl_txbuf* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mwl_desc_setup (struct mwl_softc*,char*,TYPE_1__*,int,int,int /*<<< orphan*/ ,int) ; 
 int mwl_txbuf ; 
 int /*<<< orphan*/  mwl_txq_reset (struct mwl_softc*,struct mwl_txq*) ; 

__attribute__((used)) static int
mwl_txdma_setup(struct mwl_softc *sc, struct mwl_txq *txq)
{
	int error, bsize, i;
	struct mwl_txbuf *bf;
	struct mwl_txdesc *ds;

	error = mwl_desc_setup(sc, "tx", &txq->dma,
			mwl_txbuf, sizeof(struct mwl_txbuf),
			MWL_TXDESC, sizeof(struct mwl_txdesc));
	if (error != 0)
		return error;

	/* allocate and setup tx buffers */
	bsize = mwl_txbuf * sizeof(struct mwl_txbuf);
	bf = malloc(bsize, M_MWLDEV, M_NOWAIT | M_ZERO);
	if (bf == NULL) {
		device_printf(sc->sc_dev, "malloc of %u tx buffers failed\n",
			mwl_txbuf);
		return ENOMEM;
	}
	txq->dma.dd_bufptr = bf;

	ds = txq->dma.dd_desc;
	for (i = 0; i < mwl_txbuf; i++, bf++, ds += MWL_TXDESC) {
		bf->bf_desc = ds;
		bf->bf_daddr = DS2PHYS(&txq->dma, ds);
		error = bus_dmamap_create(sc->sc_dmat, BUS_DMA_NOWAIT,
				&bf->bf_dmamap);
		if (error != 0) {
			device_printf(sc->sc_dev, "unable to create dmamap for tx "
				"buffer %u, error %u\n", i, error);
			return error;
		}
	}
	mwl_txq_reset(sc, txq);
	return 0;
}