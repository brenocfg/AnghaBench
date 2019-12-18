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
struct ste_chain_data {int /*<<< orphan*/  ste_rx_list_map; int /*<<< orphan*/  ste_rx_list_tag; TYPE_1__* ste_rx_chain; TYPE_1__* ste_rx_head; } ;
struct ste_list_data {scalar_t__ ste_rx_list_paddr; TYPE_2__* ste_rx_list; } ;
struct ste_softc {struct ste_chain_data ste_cdata; struct ste_list_data ste_ldata; scalar_t__ ste_int_rx_act; } ;
struct ste_desc_onefrag {int dummy; } ;
struct TYPE_4__ {void* ste_next; } ;
struct TYPE_3__ {struct TYPE_3__* ste_next; TYPE_2__* ste_ptr; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int STE_RX_LIST_CNT ; 
 int /*<<< orphan*/  STE_RX_LIST_SZ ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* htole32 (scalar_t__) ; 
 int ste_newbuf (struct ste_softc*,TYPE_1__*) ; 

__attribute__((used)) static int
ste_init_rx_list(struct ste_softc *sc)
{
	struct ste_chain_data *cd;
	struct ste_list_data *ld;
	int error, i;

	sc->ste_int_rx_act = 0;
	cd = &sc->ste_cdata;
	ld = &sc->ste_ldata;
	bzero(ld->ste_rx_list, STE_RX_LIST_SZ);
	for (i = 0; i < STE_RX_LIST_CNT; i++) {
		cd->ste_rx_chain[i].ste_ptr = &ld->ste_rx_list[i];
		error = ste_newbuf(sc, &cd->ste_rx_chain[i]);
		if (error != 0)
			return (error);
		if (i == (STE_RX_LIST_CNT - 1)) {
			cd->ste_rx_chain[i].ste_next = &cd->ste_rx_chain[0];
			ld->ste_rx_list[i].ste_next =
			    htole32(ld->ste_rx_list_paddr +
			    (sizeof(struct ste_desc_onefrag) * 0));
		} else {
			cd->ste_rx_chain[i].ste_next = &cd->ste_rx_chain[i + 1];
			ld->ste_rx_list[i].ste_next =
			    htole32(ld->ste_rx_list_paddr +
			    (sizeof(struct ste_desc_onefrag) * (i + 1)));
		}
	}

	cd->ste_rx_head = &cd->ste_rx_chain[0];
	bus_dmamap_sync(sc->ste_cdata.ste_rx_list_tag,
	    sc->ste_cdata.ste_rx_list_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}