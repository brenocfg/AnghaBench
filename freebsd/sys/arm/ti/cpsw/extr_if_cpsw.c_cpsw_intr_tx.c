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
struct cpsw_softc {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_CPDMA_EOI_VECTOR ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_CP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_TX_LOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  CPSW_TX_UNLOCK (struct cpsw_softc*) ; 
 int cpsw_read_4 (struct cpsw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_tx_dequeue (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpsw_write_cp (struct cpsw_softc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
cpsw_intr_tx(void *arg)
{
	struct cpsw_softc *sc;

	sc = (struct cpsw_softc *)arg;
	CPSW_TX_LOCK(sc);
	if (cpsw_read_4(sc, CPSW_CPDMA_TX_CP(0)) == 0xfffffffc)
		cpsw_write_cp(sc, &sc->tx, 0xfffffffc);
	cpsw_tx_dequeue(sc);
	cpsw_write_4(sc, CPSW_CPDMA_CPDMA_EOI_VECTOR, 2);
	CPSW_TX_UNLOCK(sc);
}