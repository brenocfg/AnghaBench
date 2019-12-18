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
struct ste_chain_data {int /*<<< orphan*/  ste_tx_list_map; int /*<<< orphan*/  ste_tx_list_tag; scalar_t__ ste_tx_cnt; scalar_t__ ste_tx_cons; scalar_t__ ste_tx_prod; int /*<<< orphan*/ * ste_last_tx; TYPE_1__* ste_tx_chain; } ;
struct ste_list_data {scalar_t__ ste_tx_list_paddr; int /*<<< orphan*/ * ste_tx_list; } ;
struct ste_softc {struct ste_chain_data ste_cdata; struct ste_list_data ste_ldata; } ;
struct ste_desc {int dummy; } ;
struct TYPE_2__ {void* ste_phys; struct TYPE_2__* ste_next; int /*<<< orphan*/ * ste_mbuf; int /*<<< orphan*/ * ste_ptr; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  STE_ADDR_LO (scalar_t__) ; 
 int STE_TX_LIST_CNT ; 
 int /*<<< orphan*/  STE_TX_LIST_SZ ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ste_init_tx_list(struct ste_softc *sc)
{
	struct ste_chain_data *cd;
	struct ste_list_data *ld;
	int i;

	cd = &sc->ste_cdata;
	ld = &sc->ste_ldata;
	bzero(ld->ste_tx_list, STE_TX_LIST_SZ);
	for (i = 0; i < STE_TX_LIST_CNT; i++) {
		cd->ste_tx_chain[i].ste_ptr = &ld->ste_tx_list[i];
		cd->ste_tx_chain[i].ste_mbuf = NULL;
		if (i == (STE_TX_LIST_CNT - 1)) {
			cd->ste_tx_chain[i].ste_next = &cd->ste_tx_chain[0];
			cd->ste_tx_chain[i].ste_phys = htole32(STE_ADDR_LO(
			    ld->ste_tx_list_paddr +
			    (sizeof(struct ste_desc) * 0)));
		} else {
			cd->ste_tx_chain[i].ste_next = &cd->ste_tx_chain[i + 1];
			cd->ste_tx_chain[i].ste_phys = htole32(STE_ADDR_LO(
			    ld->ste_tx_list_paddr +
			    (sizeof(struct ste_desc) * (i + 1))));
		}
	}

	cd->ste_last_tx = NULL;
	cd->ste_tx_prod = 0;
	cd->ste_tx_cons = 0;
	cd->ste_tx_cnt = 0;

	bus_dmamap_sync(sc->ste_cdata.ste_tx_list_tag,
	    sc->ste_cdata.ste_tx_list_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}