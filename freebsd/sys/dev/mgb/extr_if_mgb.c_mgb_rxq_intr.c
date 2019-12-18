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
typedef  int uint32_t ;
struct mgb_softc {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_3__ {int isc_nrxqsets; } ;

/* Variables and functions */
 int CSR_READ_REG (struct mgb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int) ; 
 int FILTER_SCHEDULE_THREAD ; 
 int /*<<< orphan*/  MGB_INTR_ENBL_CLR ; 
 int /*<<< orphan*/  MGB_INTR_ENBL_SET ; 
 int /*<<< orphan*/  MGB_INTR_STS ; 
 int MGB_INTR_STS_RX (int) ; 
 TYPE_1__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_rxq_intr(void *xsc)
{
	struct mgb_softc *sc;
	if_softc_ctx_t scctx;
	uint32_t intr_sts, intr_en;
	int qidx;

	sc = xsc;
	scctx = iflib_get_softc_ctx(sc->ctx);

	intr_sts = CSR_READ_REG(sc, MGB_INTR_STS);
	intr_en = CSR_READ_REG(sc, MGB_INTR_ENBL_SET);
	intr_sts &= intr_en;

	for (qidx = 0; qidx < scctx->isc_nrxqsets; qidx++) {
		if ((intr_sts & MGB_INTR_STS_RX(qidx))){
			CSR_WRITE_REG(sc, MGB_INTR_ENBL_CLR,
			    MGB_INTR_STS_RX(qidx));
			CSR_WRITE_REG(sc, MGB_INTR_STS, MGB_INTR_STS_RX(qidx));
		}
	}
	return (FILTER_SCHEDULE_THREAD);
}