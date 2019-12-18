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
typedef  int /*<<< orphan*/  uint16_t ;
struct mgb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGB_DMAC_INTR_ENBL_SET ; 
 int /*<<< orphan*/  MGB_DMAC_INTR_STS ; 
 int /*<<< orphan*/  MGB_DMAC_RX_INTR_ENBL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGB_INTR_ENBL_SET ; 
 int /*<<< orphan*/  MGB_INTR_RX_VEC_STS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGB_INTR_STS_RX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGB_INTR_VEC_ENBL_SET ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_rx_queue_intr_enable(if_ctx_t ctx, uint16_t qid)
{
	/* called after successful rx isr */
	struct mgb_softc *sc;

	sc = iflib_get_softc(ctx);
	CSR_WRITE_REG(sc, MGB_INTR_VEC_ENBL_SET, MGB_INTR_RX_VEC_STS(qid));
	CSR_WRITE_REG(sc, MGB_INTR_ENBL_SET, MGB_INTR_STS_RX(qid));

	CSR_WRITE_REG(sc, MGB_DMAC_INTR_STS, MGB_DMAC_RX_INTR_ENBL(qid));
	CSR_WRITE_REG(sc, MGB_DMAC_INTR_ENBL_SET, MGB_DMAC_RX_INTR_ENBL(qid));
	return (0);
}