#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mge_softc {size_t rx_desc_curr; int /*<<< orphan*/  mge_desc_dtag; int /*<<< orphan*/  mge_rx_dtag; struct mge_desc_wrapper* mge_rx_desc; struct ifnet* ifp; } ;
struct mge_desc_wrapper {int /*<<< orphan*/  desc_dmap; TYPE_3__* mge_desc; TYPE_1__* buffer; int /*<<< orphan*/  buffer_dmap; } ;
struct TYPE_5__ {int len; struct ifnet* rcvif; } ;
struct mbuf {int m_len; int m_data; TYPE_2__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_6__ {int cmd_status; scalar_t__ byte_count; int /*<<< orphan*/  buff_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  m_data; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 scalar_t__ ETHER_CRC_LEN ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int MGE_DMA_OWNED ; 
 int MGE_ERR_SUMMARY ; 
 int /*<<< orphan*/  MGE_RECEIVE_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_RECEIVE_LOCK_ASSERT (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_RECEIVE_UNLOCK (struct mge_softc*) ; 
 int MGE_RX_DESC_NUM ; 
 int MGE_RX_ENABLE_INT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_devget (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mge_offload_process_frame (struct ifnet*,struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
mge_intr_rx_locked(struct mge_softc *sc, int count)
{
	struct ifnet *ifp = sc->ifp;
	uint32_t status;
	uint16_t bufsize;
	struct mge_desc_wrapper* dw;
	struct mbuf *mb;
	int rx_npkts = 0;

	MGE_RECEIVE_LOCK_ASSERT(sc);

	while (count != 0) {
		dw = &sc->mge_rx_desc[sc->rx_desc_curr];
		bus_dmamap_sync(sc->mge_desc_dtag, dw->desc_dmap,
		    BUS_DMASYNC_POSTREAD);

		/* Get status */
		status = dw->mge_desc->cmd_status;
		bufsize = dw->mge_desc->buff_size;
		if ((status & MGE_DMA_OWNED) != 0)
			break;

		if (dw->mge_desc->byte_count &&
		    ~(status & MGE_ERR_SUMMARY)) {

			bus_dmamap_sync(sc->mge_rx_dtag, dw->buffer_dmap,
			    BUS_DMASYNC_POSTREAD);

			mb = m_devget(dw->buffer->m_data,
			    dw->mge_desc->byte_count - ETHER_CRC_LEN,
			    0, ifp, NULL);

			if (mb == NULL)
				/* Give up if no mbufs */
				break;

			mb->m_len -= 2;
			mb->m_pkthdr.len -= 2;
			mb->m_data += 2;

			mb->m_pkthdr.rcvif = ifp;

			mge_offload_process_frame(ifp, mb, status,
			    bufsize);

			MGE_RECEIVE_UNLOCK(sc);
			(*ifp->if_input)(ifp, mb);
			MGE_RECEIVE_LOCK(sc);
			rx_npkts++;
		}

		dw->mge_desc->byte_count = 0;
		dw->mge_desc->cmd_status = MGE_RX_ENABLE_INT | MGE_DMA_OWNED;
		sc->rx_desc_curr = (++sc->rx_desc_curr % MGE_RX_DESC_NUM);
		bus_dmamap_sync(sc->mge_desc_dtag, dw->desc_dmap,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

		if (count > 0)
			count -= 1;
	}

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, rx_npkts);

	return (rx_npkts);
}