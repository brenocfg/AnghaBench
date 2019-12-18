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
struct bnxt_softc {int /*<<< orphan*/  def_cp_ring; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_clear_ids (struct bnxt_softc*) ; 
 int /*<<< orphan*/  bnxt_do_disable_intr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_hwrm_func_reset (struct bnxt_softc*) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_stop(if_ctx_t ctx)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);

	bnxt_do_disable_intr(&softc->def_cp_ring);
	bnxt_hwrm_func_reset(softc);
	bnxt_clear_ids(softc);
	return;
}