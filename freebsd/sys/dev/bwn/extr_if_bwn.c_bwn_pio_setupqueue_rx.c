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
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_pio_rxqueue {scalar_t__ prq_base; int /*<<< orphan*/  prq_rev; struct bwn_mac* prq_mac; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 scalar_t__ BWN_PIO_RXQOFFSET (struct bwn_mac*) ; 
 int /*<<< orphan*/  bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_dma_rxdirectfifo (struct bwn_mac*,int,int) ; 
 scalar_t__ bwn_pio_idx2base (struct bwn_mac*,int) ; 

__attribute__((used)) static void
bwn_pio_setupqueue_rx(struct bwn_mac *mac, struct bwn_pio_rxqueue *prq,
    int index)
{
	struct bwn_softc *sc = mac->mac_sc;

	prq->prq_mac = mac;
	prq->prq_rev = bhnd_get_hwrev(sc->sc_dev);
	prq->prq_base = bwn_pio_idx2base(mac, index) + BWN_PIO_RXQOFFSET(mac);
	bwn_dma_rxdirectfifo(mac, index, 1);
}