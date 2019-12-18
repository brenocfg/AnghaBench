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
struct rt2560_tx_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  eiv; } ;
struct TYPE_2__ {int physaddr; int next_encrypt; int cur_encrypt; int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_dmat; struct rt2560_tx_desc* desc; } ;
struct rt2560_softc {TYPE_1__ txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  DPRINTFN (struct rt2560_softc*,int,char*,size_t) ; 
 int RAL_READ (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2560_KICK_TX ; 
 int /*<<< orphan*/  RT2560_SECCSR1 ; 
 int /*<<< orphan*/  RT2560_TXCSR0 ; 
 int RT2560_TX_BUSY ; 
 int RT2560_TX_CIPHER_BUSY ; 
 int RT2560_TX_CIPHER_MASK ; 
 int RT2560_TX_CIPHER_TKIP ; 
 int RT2560_TX_DESC_SIZE ; 
 int RT2560_TX_RING_COUNT ; 
 int RT2560_TX_VALID ; 
 int /*<<< orphan*/  bswap32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void
rt2560_encryption_intr(struct rt2560_softc *sc)
{
	struct rt2560_tx_desc *desc;
	int hw;

	/* retrieve last descriptor index processed by cipher engine */
	hw = RAL_READ(sc, RT2560_SECCSR1) - sc->txq.physaddr;
	hw /= RT2560_TX_DESC_SIZE;

	bus_dmamap_sync(sc->txq.desc_dmat, sc->txq.desc_map,
	    BUS_DMASYNC_POSTREAD);

	while (sc->txq.next_encrypt != hw) {
		if (sc->txq.next_encrypt == sc->txq.cur_encrypt) {
			printf("hw encrypt %d, cur_encrypt %d\n", hw,
			    sc->txq.cur_encrypt);
			break;
		}

		desc = &sc->txq.desc[sc->txq.next_encrypt];

		if ((le32toh(desc->flags) & RT2560_TX_BUSY) ||
		    (le32toh(desc->flags) & RT2560_TX_CIPHER_BUSY))
			break;

		/* for TKIP, swap eiv field to fix a bug in ASIC */
		if ((le32toh(desc->flags) & RT2560_TX_CIPHER_MASK) ==
		    RT2560_TX_CIPHER_TKIP)
			desc->eiv = bswap32(desc->eiv);

		/* mark the frame ready for transmission */
		desc->flags |= htole32(RT2560_TX_VALID);
		desc->flags |= htole32(RT2560_TX_BUSY);

		DPRINTFN(sc, 15, "encryption done idx=%u\n",
		    sc->txq.next_encrypt);

		sc->txq.next_encrypt =
		    (sc->txq.next_encrypt + 1) % RT2560_TX_RING_COUNT;
	}

	bus_dmamap_sync(sc->txq.desc_dmat, sc->txq.desc_map,
	    BUS_DMASYNC_PREWRITE);

	/* kick Tx */
	RAL_WRITE(sc, RT2560_TXCSR0, RT2560_KICK_TX);
}