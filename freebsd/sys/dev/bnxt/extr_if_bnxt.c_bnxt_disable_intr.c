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
struct bnxt_softc {int ntxqsets; int nrxqsets; int /*<<< orphan*/ * rx_cp_rings; int /*<<< orphan*/ * tx_cp_rings; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_do_disable_intr (int /*<<< orphan*/ *) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_disable_intr(if_ctx_t ctx)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);
	int i;

	/*
	 * NOTE: These TX interrupts should never get enabled, so don't
	 * update the index
	 */
	for (i = 0; i < softc->ntxqsets; i++)
		bnxt_do_disable_intr(&softc->tx_cp_rings[i]);
	for (i = 0; i < softc->nrxqsets; i++)
		bnxt_do_disable_intr(&softc->rx_cp_rings[i]);

	return;
}