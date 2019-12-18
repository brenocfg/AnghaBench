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
struct bxe_softc {scalar_t__ wol; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  tx_ring_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_BD_USABLE ; 
 int /*<<< orphan*/  TX_BD_USABLE ; 
 int /*<<< orphan*/  bxe_get_tunable_params (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_get_params(struct bxe_softc *sc)
{
    /* get user tunable params */
    bxe_get_tunable_params(sc);

    /* select the RX and TX ring sizes */
    sc->tx_ring_size = TX_BD_USABLE;
    sc->rx_ring_size = RX_BD_USABLE;

    /* XXX disable WoL */
    sc->wol = 0;
}