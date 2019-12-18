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
struct rx_bd {void* rx_bd_haddr_lo; void* rx_bd_haddr_hi; } ;
struct bce_softc {int rx_pages; int /*<<< orphan*/ * rx_bd_chain_map; int /*<<< orphan*/  rx_bd_chain_tag; void* rx_empty_count; void* rx_low_watermark; int /*<<< orphan*/ * rx_bd_chain_paddr; struct rx_bd** rx_bd_chain; void* max_rx_bd; void* free_rx_bd; scalar_t__ rx_prod_bseq; scalar_t__ rx_cons; scalar_t__ rx_prod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_ADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCE_EXTREME_RECV ; 
 int BCE_VERBOSE_CTX ; 
 int BCE_VERBOSE_LOAD ; 
 int BCE_VERBOSE_RECV ; 
 int BCE_VERBOSE_RESET ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  DBENTER (int) ; 
 int /*<<< orphan*/  DBEXIT (int) ; 
 int /*<<< orphan*/  DBRUN (void*) ; 
 int /*<<< orphan*/  DBRUNMSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOTAL_RX_BD_ALLOC ; 
 void* USABLE_RX_BD_ALLOC ; 
 size_t USABLE_RX_BD_PER_PAGE ; 
 int /*<<< orphan*/  bce_dump_rx_bd_chain (struct bce_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_fill_rx_chain (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_init_rx_context (struct bce_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bce_init_rx_chain(struct bce_softc *sc)
{
	struct rx_bd *rxbd;
	int i, rc = 0;

	DBENTER(BCE_VERBOSE_RESET | BCE_VERBOSE_RECV | BCE_VERBOSE_LOAD |
	    BCE_VERBOSE_CTX);

	/* Initialize the RX producer and consumer indices. */
	sc->rx_prod        = 0;
	sc->rx_cons        = 0;
	sc->rx_prod_bseq   = 0;
	sc->free_rx_bd     = USABLE_RX_BD_ALLOC;
	sc->max_rx_bd      = USABLE_RX_BD_ALLOC;

	/* Initialize the RX next pointer chain entries. */
	for (i = 0; i < sc->rx_pages; i++) {
		int j;

		rxbd = &sc->rx_bd_chain[i][USABLE_RX_BD_PER_PAGE];

		/* Check if we've reached the last page. */
		if (i == (sc->rx_pages - 1))
			j = 0;
		else
			j = i + 1;

		/* Setup the chain page pointers. */
		rxbd->rx_bd_haddr_hi =
		    htole32(BCE_ADDR_HI(sc->rx_bd_chain_paddr[j]));
		rxbd->rx_bd_haddr_lo =
		    htole32(BCE_ADDR_LO(sc->rx_bd_chain_paddr[j]));
	}

	/* Fill up the RX chain. */
	bce_fill_rx_chain(sc);

	DBRUN(sc->rx_low_watermark = USABLE_RX_BD_ALLOC);
	DBRUN(sc->rx_empty_count = 0);
	for (i = 0; i < sc->rx_pages; i++) {
		bus_dmamap_sync(sc->rx_bd_chain_tag, sc->rx_bd_chain_map[i],
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}

	bce_init_rx_context(sc);

	DBRUNMSG(BCE_EXTREME_RECV,
	    bce_dump_rx_bd_chain(sc, 0, TOTAL_RX_BD_ALLOC));
	DBEXIT(BCE_VERBOSE_RESET | BCE_VERBOSE_RECV | BCE_VERBOSE_LOAD |
	    BCE_VERBOSE_CTX);

	/* ToDo: Are there possible failure modes here? */

	return(rc);
}