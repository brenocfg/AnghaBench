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
struct TYPE_3__ {int isc_nrxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MGB_DMAC_INTR_ENBL_SET ; 
 int /*<<< orphan*/  MGB_DMAC_INTR_STS ; 
 int MGB_DMAC_RX_INTR_ENBL (int) ; 
 int /*<<< orphan*/  MGB_INTR_ENBL_SET ; 
 int MGB_INTR_RX_VEC_STS (int) ; 
 int MGB_INTR_STS_ANY ; 
 int MGB_INTR_STS_RX (int) ; 
 int /*<<< orphan*/  MGB_INTR_VEC_ENBL_SET ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_1__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mgb_intr_enable_all(if_ctx_t ctx)
{
	struct mgb_softc *sc;
	if_softc_ctx_t scctx;
	int i, dmac_enable = 0, intr_sts = 0, vec_en = 0;

	sc = iflib_get_softc(ctx);
	scctx = iflib_get_softc_ctx(ctx);
	intr_sts |= MGB_INTR_STS_ANY;
	vec_en |= MGB_INTR_STS_ANY;

	for (i = 0; i < scctx->isc_nrxqsets; i++) {
		intr_sts |= MGB_INTR_STS_RX(i);
		dmac_enable |= MGB_DMAC_RX_INTR_ENBL(i);
		vec_en |= MGB_INTR_RX_VEC_STS(i);
	}

	/* TX interrupts aren't needed ... */

	CSR_WRITE_REG(sc, MGB_INTR_ENBL_SET, intr_sts);
	CSR_WRITE_REG(sc, MGB_INTR_VEC_ENBL_SET, vec_en);
	CSR_WRITE_REG(sc, MGB_DMAC_INTR_STS, dmac_enable);
	CSR_WRITE_REG(sc, MGB_DMAC_INTR_ENBL_SET, dmac_enable);
}