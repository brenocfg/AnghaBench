#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mgb_softc {int dummy; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_3__ {int isc_nrxqsets; int isc_ntxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_STOP ; 
 int /*<<< orphan*/  FCT_DISABLE ; 
 int /*<<< orphan*/  MGB_DMAC_RX_START ; 
 int /*<<< orphan*/  MGB_DMAC_TX_START ; 
 int /*<<< orphan*/  MGB_FCT_RX_CTL ; 
 int /*<<< orphan*/  MGB_FCT_TX_CTL ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_1__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgb_dmac_control (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgb_fct_control (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mgb_stop(if_ctx_t ctx)
{
	struct mgb_softc *sc ;
	if_softc_ctx_t scctx;
	int i;

	sc = iflib_get_softc(ctx);
	scctx = iflib_get_softc_ctx(ctx);

	/* XXX: Could potentially timeout */
	for (i = 0; i < scctx->isc_nrxqsets; i++) {
		mgb_dmac_control(sc, MGB_DMAC_RX_START, 0, DMAC_STOP);
		mgb_fct_control(sc, MGB_FCT_RX_CTL, 0, FCT_DISABLE);
	}
	for (i = 0; i < scctx->isc_ntxqsets; i++) {
		mgb_dmac_control(sc, MGB_DMAC_TX_START, 0, DMAC_STOP);
		mgb_fct_control(sc, MGB_FCT_TX_CTL, 0, FCT_DISABLE);
	}
}