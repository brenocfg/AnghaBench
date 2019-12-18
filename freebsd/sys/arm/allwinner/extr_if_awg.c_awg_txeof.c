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
struct emac_desc {int /*<<< orphan*/  size; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int next; scalar_t__ queued; struct emac_desc* desc_ring; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; } ;
struct awg_softc {TYPE_1__ tx; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_ASSERT_LOCKED (struct awg_softc*) ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int TX_DESC_CTL ; 
 int TX_HEADER_ERR ; 
 int TX_LAST_DESC ; 
 int TX_NEXT (int) ; 
 int TX_PAYLOAD_ERR ; 
 int /*<<< orphan*/  awg_clean_txbuf (struct awg_softc*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
awg_txeof(struct awg_softc *sc)
{
	struct emac_desc *desc;
	uint32_t status, size;
	if_t ifp;
	int i, prog;

	AWG_ASSERT_LOCKED(sc);

	bus_dmamap_sync(sc->tx.desc_tag, sc->tx.desc_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	ifp = sc->ifp;

	prog = 0;
	for (i = sc->tx.next; sc->tx.queued > 0; i = TX_NEXT(i)) {
		desc = &sc->tx.desc_ring[i];
		status = le32toh(desc->status);
		if ((status & TX_DESC_CTL) != 0)
			break;
		size = le32toh(desc->size);
		if (size & TX_LAST_DESC) {
			if ((status & (TX_HEADER_ERR | TX_PAYLOAD_ERR)) != 0)
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			else
				if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		}
		prog++;
		awg_clean_txbuf(sc, i);
	}

	if (prog > 0) {
		sc->tx.next = i;
		if_setdrvflagbits(ifp, 0, IFF_DRV_OACTIVE);
	}
}