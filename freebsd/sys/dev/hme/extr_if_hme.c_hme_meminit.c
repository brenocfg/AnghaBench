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
typedef  int /*<<< orphan*/  u_long ;
typedef  void* u_int32_t ;
struct hme_txdesc {int /*<<< orphan*/ * htx_m; int /*<<< orphan*/  htx_dmamap; } ;
struct hme_ring {void* rb_txd; void* rb_rxd; void* rb_rxddma; void* rb_txddma; scalar_t__ rb_rdtail; scalar_t__ rb_td_nbusy; scalar_t__ rb_tdtail; scalar_t__ rb_tdhead; int /*<<< orphan*/  rb_txfreeq; struct hme_txdesc* rb_txdesc; int /*<<< orphan*/  rb_txbusyq; void* rb_dmabase; void* rb_membase; } ;
struct hme_softc {int sc_flags; int /*<<< orphan*/  sc_cdmamap; int /*<<< orphan*/  sc_cdmatag; struct hme_ring sc_rb; int /*<<< orphan*/  sc_tdmatag; } ;
typedef  void* caddr_t ;
typedef  void* bus_addr_t ;

/* Variables and functions */
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,void*,void*) ; 
 unsigned int HME_NRXDESC ; 
 unsigned int HME_NTXDESC ; 
 unsigned int HME_NTXQ ; 
 int HME_PCI ; 
 int /*<<< orphan*/  HME_XD_SETADDR (int,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_XD_SETFLAGS (int,void*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int HME_XD_SIZE ; 
 int /*<<< orphan*/  KTR_HME ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct hme_txdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hme_add_rxbuf (struct hme_softc*,unsigned int,int) ; 
 int /*<<< orphan*/  htx_q ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 scalar_t__ roundup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hme_meminit(struct hme_softc *sc)
{
	struct hme_ring *hr = &sc->sc_rb;
	struct hme_txdesc *td;
	bus_addr_t dma;
	caddr_t p;
	unsigned int i;
	int error;

	p = hr->rb_membase;
	dma = hr->rb_dmabase;

	/*
	 * Allocate transmit descriptors
	 */
	hr->rb_txd = p;
	hr->rb_txddma = dma;
	p += HME_NTXDESC * HME_XD_SIZE;
	dma += HME_NTXDESC * HME_XD_SIZE;
	/*
	 * We have reserved descriptor space until the next 2048 byte
	 * boundary.
	 */
	dma = (bus_addr_t)roundup((u_long)dma, 2048);
	p = (caddr_t)roundup((u_long)p, 2048);

	/*
	 * Allocate receive descriptors
	 */
	hr->rb_rxd = p;
	hr->rb_rxddma = dma;
	p += HME_NRXDESC * HME_XD_SIZE;
	dma += HME_NRXDESC * HME_XD_SIZE;
	/* Again move forward to the next 2048 byte boundary.*/
	dma = (bus_addr_t)roundup((u_long)dma, 2048);
	p = (caddr_t)roundup((u_long)p, 2048);

	/*
	 * Initialize transmit buffer descriptors
	 */
	for (i = 0; i < HME_NTXDESC; i++) {
		HME_XD_SETADDR(sc->sc_flags & HME_PCI, hr->rb_txd, i, 0);
		HME_XD_SETFLAGS(sc->sc_flags & HME_PCI, hr->rb_txd, i, 0);
	}

	STAILQ_INIT(&sc->sc_rb.rb_txfreeq);
	STAILQ_INIT(&sc->sc_rb.rb_txbusyq);
	for (i = 0; i < HME_NTXQ; i++) {
		td = &sc->sc_rb.rb_txdesc[i];
		if (td->htx_m != NULL) {
			bus_dmamap_sync(sc->sc_tdmatag, td->htx_dmamap,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->sc_tdmatag, td->htx_dmamap);
			m_freem(td->htx_m);
			td->htx_m = NULL;
		}
		STAILQ_INSERT_TAIL(&sc->sc_rb.rb_txfreeq, td, htx_q);
	}

	/*
	 * Initialize receive buffer descriptors
	 */
	for (i = 0; i < HME_NRXDESC; i++) {
		error = hme_add_rxbuf(sc, i, 1);
		if (error != 0)
			return (error);
	}

	bus_dmamap_sync(sc->sc_cdmatag, sc->sc_cdmamap,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	hr->rb_tdhead = hr->rb_tdtail = 0;
	hr->rb_td_nbusy = 0;
	hr->rb_rdtail = 0;
	CTR2(KTR_HME, "hme_meminit: tx ring va %p, pa %#lx", hr->rb_txd,
	    hr->rb_txddma);
	CTR2(KTR_HME, "hme_meminit: rx ring va %p, pa %#lx", hr->rb_rxd,
	    hr->rb_rxddma);
	CTR2(KTR_HME, "rx entry 1: flags %x, address %x",
	    *(u_int32_t *)hr->rb_rxd, *(u_int32_t *)(hr->rb_rxd + 4));
	CTR2(KTR_HME, "tx entry 1: flags %x, address %x",
	    *(u_int32_t *)hr->rb_txd, *(u_int32_t *)(hr->rb_txd + 4));
	return (0);
}