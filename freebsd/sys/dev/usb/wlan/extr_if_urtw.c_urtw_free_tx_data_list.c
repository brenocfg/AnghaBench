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
struct urtw_softc {int /*<<< orphan*/  sc_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_TX_DATA_LIST_COUNT ; 
 int /*<<< orphan*/  urtw_free_data_list (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
urtw_free_tx_data_list(struct urtw_softc *sc)
{
	urtw_free_data_list(sc, sc->sc_tx, URTW_TX_DATA_LIST_COUNT, 0);
}