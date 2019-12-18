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
struct malo_txq {int dummy; } ;
struct malo_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALO_TXQ_LOCK_DESTROY (struct malo_txq*) ; 

__attribute__((used)) static void
malo_tx_cleanupq(struct malo_softc *sc, struct malo_txq *txq)
{
	/* XXX hal work? */
	MALO_TXQ_LOCK_DESTROY(txq);
}