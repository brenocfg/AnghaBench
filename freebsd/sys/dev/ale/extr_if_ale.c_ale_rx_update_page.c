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
typedef  scalar_t__ uint32_t ;
struct rx_rs {int dummy; } ;
struct TYPE_2__ {int ale_rx_curp; struct ale_rx_page* ale_rx_page; } ;
struct ale_softc {TYPE_1__ ale_cdata; } ;
struct ale_rx_page {scalar_t__ cons; scalar_t__* cmb_addr; int /*<<< orphan*/  cmb_map; int /*<<< orphan*/  cmb_tag; int /*<<< orphan*/  page_map; int /*<<< orphan*/  page_tag; } ;

/* Variables and functions */
 scalar_t__ ALE_RXF0_PAGE0 ; 
 int /*<<< orphan*/  ALE_RX_PAGE_ALIGN ; 
 scalar_t__ ALE_RX_PAGE_SZ ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct ale_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXF_VALID ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ale_rx_update_page(struct ale_softc *sc, struct ale_rx_page **page,
    uint32_t length, uint32_t *prod)
{
	struct ale_rx_page *rx_page;

	rx_page = *page;
	/* Update consumer position. */
	rx_page->cons += roundup(length + sizeof(struct rx_rs),
	    ALE_RX_PAGE_ALIGN);
	if (rx_page->cons >= ALE_RX_PAGE_SZ) {
		/*
		 * End of Rx page reached, let hardware reuse
		 * this page.
		 */
		rx_page->cons = 0;
		*rx_page->cmb_addr = 0;
		bus_dmamap_sync(rx_page->cmb_tag, rx_page->cmb_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		CSR_WRITE_1(sc, ALE_RXF0_PAGE0 + sc->ale_cdata.ale_rx_curp,
		    RXF_VALID);
		/* Switch to alternate Rx page. */
		sc->ale_cdata.ale_rx_curp ^= 1;
		rx_page = *page =
		    &sc->ale_cdata.ale_rx_page[sc->ale_cdata.ale_rx_curp];
		/* Page flipped, sync CMB and Rx page. */
		bus_dmamap_sync(rx_page->page_tag, rx_page->page_map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		bus_dmamap_sync(rx_page->cmb_tag, rx_page->cmb_map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		/* Sync completed, cache updated producer index. */
		*prod = *rx_page->cmb_addr;
	}
}