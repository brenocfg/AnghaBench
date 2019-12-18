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
struct mwl_txq {int dummy; } ;
struct mwl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWL_TXQ_LOCK_DESTROY (struct mwl_txq*) ; 

__attribute__((used)) static void
mwl_tx_cleanupq(struct mwl_softc *sc, struct mwl_txq *txq)
{
	/* XXX hal work? */
	MWL_TXQ_LOCK_DESTROY(txq);
}