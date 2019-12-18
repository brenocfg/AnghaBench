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
struct bnxt_softc {int nrxqsets; int /*<<< orphan*/ * rx_cp_rings; int /*<<< orphan*/  def_cp_ring; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_do_enable_intr (int /*<<< orphan*/ *) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_intr_enable(if_ctx_t ctx)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);
	int i;

	bnxt_do_enable_intr(&softc->def_cp_ring);
	for (i = 0; i < softc->nrxqsets; i++)
		bnxt_do_enable_intr(&softc->rx_cp_rings[i]);

	return;
}