#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct ifnet {int dummy; } ;
struct TYPE_4__ {int fv_tx_prod; int /*<<< orphan*/  fv_sf_buff_map; int /*<<< orphan*/  fv_sf_tag; int /*<<< orphan*/  fv_tx_ring_map; int /*<<< orphan*/  fv_tx_ring_tag; scalar_t__ fv_sf_buff; int /*<<< orphan*/  fv_tx_cnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  fv_sf_paddr; struct fv_desc* fv_tx_ring; } ;
struct fv_softc {TYPE_2__ fv_cdata; struct ifnet* fv_ifp; TYPE_1__ fv_rdata; } ;
struct fv_desc {int fv_devcs; int /*<<< orphan*/  fv_stat; int /*<<< orphan*/  fv_addr; } ;

/* Variables and functions */
 int ADCTL_Tx_SETUP ; 
 int /*<<< orphan*/  ADSTAT_OWN ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_TXPOLL ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct fv_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int FV_DMASIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FV_INC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FV_SFRAME_LEN ; 
 int /*<<< orphan*/  FV_TX_RING_CNT ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fv_set_maddr ; 
 int if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fv_setfilt(struct fv_softc *sc)
{
	uint16_t eaddr[(ETHER_ADDR_LEN+1)/2];
	struct fv_desc *sframe;
	int i;
	struct ifnet *ifp;
	uint16_t *sp;

	ifp = sc->fv_ifp;

	i = sc->fv_cdata.fv_tx_prod;
	FV_INC(sc->fv_cdata.fv_tx_prod, FV_TX_RING_CNT);
	sc->fv_cdata.fv_tx_cnt++;
	sframe = &sc->fv_rdata.fv_tx_ring[i];
	sp = (uint16_t *)sc->fv_cdata.fv_sf_buff;
	memset(sp, 0xff, FV_SFRAME_LEN);
	
	sframe->fv_addr = sc->fv_rdata.fv_sf_paddr;
	sframe->fv_devcs = ADCTL_Tx_SETUP | FV_DMASIZE(FV_SFRAME_LEN);

	i = if_foreach_llmaddr(ifp, fv_set_maddr, sp) * 6;

	bcopy(IF_LLADDR(sc->fv_ifp), eaddr, ETHER_ADDR_LEN);
	sp[90] = sp[91] = eaddr[0];
	sp[92] = sp[93] = eaddr[1];
	sp[94] = sp[95] = eaddr[2];

	sframe->fv_stat = ADSTAT_OWN;
	bus_dmamap_sync(sc->fv_cdata.fv_tx_ring_tag,
	    sc->fv_cdata.fv_tx_ring_map, BUS_DMASYNC_PREWRITE);
	bus_dmamap_sync(sc->fv_cdata.fv_sf_tag,
	    sc->fv_cdata.fv_sf_buff_map, BUS_DMASYNC_PREWRITE);
	CSR_WRITE_4(sc, CSR_TXPOLL, 0xFFFFFFFF);
	DELAY(10000);
}