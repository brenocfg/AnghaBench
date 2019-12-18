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
typedef  int uint32_t ;
struct mbuf {int dummy; } ;
struct cgem_softc {scalar_t__ txring_queued; size_t txring_tl_ptr; int /*<<< orphan*/  ifp; TYPE_1__* txring; int /*<<< orphan*/  dev; struct mbuf** txring_m; int /*<<< orphan*/ ** txring_m_dmamap; int /*<<< orphan*/  mbuf_dma_tag; } ;
struct TYPE_2__ {int ctl; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CGEM_ASSERT_LOCKED (struct cgem_softc*) ; 
 int CGEM_TXDESC_AHB_ERR ; 
 int CGEM_TXDESC_LAST_BUF ; 
 int CGEM_TXDESC_LATE_COLL ; 
 int CGEM_TXDESC_RETRY_ERR ; 
 int CGEM_TXDESC_USED ; 
 int CGEM_TXDESC_WRAP ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
cgem_clean_tx(struct cgem_softc *sc)
{
	struct mbuf *m;
	uint32_t ctl;

	CGEM_ASSERT_LOCKED(sc);

	/* free up finished transmits. */
	while (sc->txring_queued > 0 &&
	       ((ctl = sc->txring[sc->txring_tl_ptr].ctl) &
		CGEM_TXDESC_USED) != 0) {

		/* Sync cache. */
		bus_dmamap_sync(sc->mbuf_dma_tag,
				sc->txring_m_dmamap[sc->txring_tl_ptr],
				BUS_DMASYNC_POSTWRITE);

		/* Unload and destroy DMA map. */
		bus_dmamap_unload(sc->mbuf_dma_tag,
				  sc->txring_m_dmamap[sc->txring_tl_ptr]);
		bus_dmamap_destroy(sc->mbuf_dma_tag,
				   sc->txring_m_dmamap[sc->txring_tl_ptr]);
		sc->txring_m_dmamap[sc->txring_tl_ptr] = NULL;

		/* Free up the mbuf. */
		m = sc->txring_m[sc->txring_tl_ptr];
		sc->txring_m[sc->txring_tl_ptr] = NULL;
		m_freem(m);

		/* Check the status. */
		if ((ctl & CGEM_TXDESC_AHB_ERR) != 0) {
			/* Serious bus error. log to console. */
			device_printf(sc->dev, "cgem_clean_tx: Whoa! "
				   "AHB error, addr=0x%x\n",
				   sc->txring[sc->txring_tl_ptr].addr);
		} else if ((ctl & (CGEM_TXDESC_RETRY_ERR |
				   CGEM_TXDESC_LATE_COLL)) != 0) {
			if_inc_counter(sc->ifp, IFCOUNTER_OERRORS, 1);
		} else
			if_inc_counter(sc->ifp, IFCOUNTER_OPACKETS, 1);

		/* If the packet spanned more than one tx descriptor,
		 * skip descriptors until we find the end so that only
		 * start-of-frame descriptors are processed.
		 */
		while ((ctl & CGEM_TXDESC_LAST_BUF) == 0) {
			if ((ctl & CGEM_TXDESC_WRAP) != 0)
				sc->txring_tl_ptr = 0;
			else
				sc->txring_tl_ptr++;
			sc->txring_queued--;

			ctl = sc->txring[sc->txring_tl_ptr].ctl;

			sc->txring[sc->txring_tl_ptr].ctl =
				ctl | CGEM_TXDESC_USED;
		}

		/* Next descriptor. */
		if ((ctl & CGEM_TXDESC_WRAP) != 0)
			sc->txring_tl_ptr = 0;
		else
			sc->txring_tl_ptr++;
		sc->txring_queued--;

		if_setdrvflagbits(sc->ifp, 0, IFF_DRV_OACTIVE);
	}
}