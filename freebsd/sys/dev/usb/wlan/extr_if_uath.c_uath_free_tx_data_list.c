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
struct uath_softc {int /*<<< orphan*/  sc_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  UATH_TX_DATA_LIST_COUNT ; 
 int /*<<< orphan*/  uath_free_data_list (struct uath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uath_free_tx_data_list(struct uath_softc *sc)
{
	uath_free_data_list(sc, sc->sc_tx, UATH_TX_DATA_LIST_COUNT,
	    0 /* no mbufs */);
}