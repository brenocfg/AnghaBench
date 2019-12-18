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
struct TYPE_6__ {struct fxp_rx* rx_tail; struct fxp_rx* rx_head; } ;
struct fxp_softc {TYPE_3__ fxp_desc; int /*<<< orphan*/  fxp_rxmtag; } ;
struct fxp_rx {struct fxp_rx* rx_next; int /*<<< orphan*/  rx_map; int /*<<< orphan*/  rx_addr; TYPE_2__* rx_mbuf; } ;
struct fxp_rfa {scalar_t__ rfa_control; int /*<<< orphan*/  link_addr; } ;
struct TYPE_4__ {scalar_t__ ext_buf; } ;
struct TYPE_5__ {TYPE_1__ m_ext; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 scalar_t__ RFA_ALIGNMENT_FUDGE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fxp_add_rfabuf(struct fxp_softc *sc, struct fxp_rx *rxp)
{
	struct fxp_rfa *p_rfa;
	struct fxp_rx *p_rx;

	/*
	 * If there are other buffers already on the list, attach this
	 * one to the end by fixing up the tail to point to this one.
	 */
	if (sc->fxp_desc.rx_head != NULL) {
		p_rx = sc->fxp_desc.rx_tail;
		p_rfa = (struct fxp_rfa *)
		    (p_rx->rx_mbuf->m_ext.ext_buf + RFA_ALIGNMENT_FUDGE);
		p_rx->rx_next = rxp;
		le32enc(&p_rfa->link_addr, rxp->rx_addr);
		p_rfa->rfa_control = 0;
		bus_dmamap_sync(sc->fxp_rxmtag, p_rx->rx_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	} else {
		rxp->rx_next = NULL;
		sc->fxp_desc.rx_head = rxp;
	}
	sc->fxp_desc.rx_tail = rxp;
}