#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;
struct TYPE_8__ {scalar_t__ l; scalar_t__ add; scalar_t__ ubound; } ;
struct TYPE_7__ {int l; int add; int ubound; } ;
struct TYPE_6__ {scalar_t__ l; scalar_t__ add; scalar_t__ ubound; } ;
struct TYPE_5__ {int l; int add; int ubound; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_FPGA (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,...) ; 
 int MAX_RD_ORD ; 
 int MAX_WR_ORD ; 
 int NUM_RD_Q ; 
 int NUM_WR_Q ; 
 scalar_t__ PCIE_REG_PCIER_TL_HDR_FC_ST ; 
 scalar_t__ PXP2_REG_PGL_TAGS_LIMIT ; 
 scalar_t__ PXP2_REG_PSWRQ_BW_RD ; 
 scalar_t__ PXP2_REG_PSWRQ_BW_WR ; 
 scalar_t__ PXP2_REG_RQ_BW_WR_L29 ; 
 scalar_t__ PXP2_REG_RQ_BW_WR_L30 ; 
 scalar_t__ PXP2_REG_RQ_PDR_LIMIT ; 
 scalar_t__ PXP2_REG_RQ_RD_MBS0 ; 
 scalar_t__ PXP2_REG_RQ_RD_MBS1 ; 
 scalar_t__ PXP2_REG_RQ_WR_MBS0 ; 
 scalar_t__ PXP2_REG_RQ_WR_MBS1 ; 
 scalar_t__ PXP2_REG_WR_CDU_MPS ; 
 scalar_t__ PXP2_REG_WR_CSDM_MPS ; 
 scalar_t__ PXP2_REG_WR_DBG_MPS ; 
 scalar_t__ PXP2_REG_WR_DMAE_MPS ; 
 scalar_t__ PXP2_REG_WR_HC_MPS ; 
 scalar_t__ PXP2_REG_WR_QM_MPS ; 
 scalar_t__ PXP2_REG_WR_SRC_MPS ; 
 scalar_t__ PXP2_REG_WR_TM_MPS ; 
 scalar_t__ PXP2_REG_WR_TSDM_MPS ; 
 scalar_t__ PXP2_REG_WR_USDMDP_TH ; 
 scalar_t__ PXP2_REG_WR_USDM_MPS ; 
 scalar_t__ PXP2_REG_WR_XSDM_MPS ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 TYPE_4__* read_arb_addr ; 
 TYPE_3__** read_arb_data ; 
 TYPE_2__* write_arb_addr ; 
 TYPE_1__** write_arb_data ; 

__attribute__((used)) static void ecore_init_pxp_arb(struct bxe_softc *sc, int r_order,
			       int w_order)
{
	uint32_t val, i;

	if (r_order > MAX_RD_ORD) {
		ECORE_MSG(sc, "read order of %d  order adjusted to %d\n",
			   r_order, MAX_RD_ORD);
		r_order = MAX_RD_ORD;
	}
	if (w_order > MAX_WR_ORD) {
		ECORE_MSG(sc, "write order of %d  order adjusted to %d\n",
			   w_order, MAX_WR_ORD);
		w_order = MAX_WR_ORD;
	}
	if (CHIP_REV_IS_FPGA(sc)) {
		ECORE_MSG(sc, "write order adjusted to 1 for FPGA\n");
		w_order = 0;
	}
	ECORE_MSG(sc, "read order %d  write order %d\n", r_order, w_order);

	for (i = 0; i < NUM_RD_Q-1; i++) {
		REG_WR(sc, read_arb_addr[i].l, read_arb_data[i][r_order].l);
		REG_WR(sc, read_arb_addr[i].add,
		       read_arb_data[i][r_order].add);
		REG_WR(sc, read_arb_addr[i].ubound,
		       read_arb_data[i][r_order].ubound);
	}

	for (i = 0; i < NUM_WR_Q-1; i++) {
		if ((write_arb_addr[i].l == PXP2_REG_RQ_BW_WR_L29) ||
		    (write_arb_addr[i].l == PXP2_REG_RQ_BW_WR_L30)) {

			REG_WR(sc, write_arb_addr[i].l,
			       write_arb_data[i][w_order].l);

			REG_WR(sc, write_arb_addr[i].add,
			       write_arb_data[i][w_order].add);

			REG_WR(sc, write_arb_addr[i].ubound,
			       write_arb_data[i][w_order].ubound);
		} else {

			val = REG_RD(sc, write_arb_addr[i].l);
			REG_WR(sc, write_arb_addr[i].l,
			       val | (write_arb_data[i][w_order].l << 10));

			val = REG_RD(sc, write_arb_addr[i].add);
			REG_WR(sc, write_arb_addr[i].add,
			       val | (write_arb_data[i][w_order].add << 10));

			val = REG_RD(sc, write_arb_addr[i].ubound);
			REG_WR(sc, write_arb_addr[i].ubound,
			       val | (write_arb_data[i][w_order].ubound << 7));
		}
	}

	val =  write_arb_data[NUM_WR_Q-1][w_order].add;
	val += write_arb_data[NUM_WR_Q-1][w_order].ubound << 10;
	val += write_arb_data[NUM_WR_Q-1][w_order].l << 17;
	REG_WR(sc, PXP2_REG_PSWRQ_BW_RD, val);

	val =  read_arb_data[NUM_RD_Q-1][r_order].add;
	val += read_arb_data[NUM_RD_Q-1][r_order].ubound << 10;
	val += read_arb_data[NUM_RD_Q-1][r_order].l << 17;
	REG_WR(sc, PXP2_REG_PSWRQ_BW_WR, val);

	REG_WR(sc, PXP2_REG_RQ_WR_MBS0, w_order);
	REG_WR(sc, PXP2_REG_RQ_WR_MBS1, w_order);
	REG_WR(sc, PXP2_REG_RQ_RD_MBS0, r_order);
	REG_WR(sc, PXP2_REG_RQ_RD_MBS1, r_order);

	if ((CHIP_IS_E1(sc) || CHIP_IS_E1H(sc)) && (r_order == MAX_RD_ORD))
		REG_WR(sc, PXP2_REG_RQ_PDR_LIMIT, 0xe00);

	if (CHIP_IS_E3(sc))
		REG_WR(sc, PXP2_REG_WR_USDMDP_TH, (0x4 << w_order));
	else if (CHIP_IS_E2(sc))
		REG_WR(sc, PXP2_REG_WR_USDMDP_TH, (0x8 << w_order));
	else
		REG_WR(sc, PXP2_REG_WR_USDMDP_TH, (0x18 << w_order));

	if (!CHIP_IS_E1(sc)) {
		/*    MPS      w_order     optimal TH      presently TH
		 *    128         0             0               2
		 *    256         1             1               3
		 *    >=512       2             2               3
		 */
		/* DMAE is special */
		if (!CHIP_IS_E1H(sc)) {
			/* E2 can use optimal TH */
			val = w_order;
			REG_WR(sc, PXP2_REG_WR_DMAE_MPS, val);
		} else {
			val = ((w_order == 0) ? 2 : 3);
			REG_WR(sc, PXP2_REG_WR_DMAE_MPS, 2);
		}

		REG_WR(sc, PXP2_REG_WR_HC_MPS, val);
		REG_WR(sc, PXP2_REG_WR_USDM_MPS, val);
		REG_WR(sc, PXP2_REG_WR_CSDM_MPS, val);
		REG_WR(sc, PXP2_REG_WR_TSDM_MPS, val);
		REG_WR(sc, PXP2_REG_WR_XSDM_MPS, val);
		REG_WR(sc, PXP2_REG_WR_QM_MPS, val);
		REG_WR(sc, PXP2_REG_WR_TM_MPS, val);
		REG_WR(sc, PXP2_REG_WR_SRC_MPS, val);
		REG_WR(sc, PXP2_REG_WR_DBG_MPS, val);
		REG_WR(sc, PXP2_REG_WR_CDU_MPS, val);
	}

	/* Validate number of tags suppoted by device */
#define PCIE_REG_PCIER_TL_HDR_FC_ST		0x2980
	val = REG_RD(sc, PCIE_REG_PCIER_TL_HDR_FC_ST);
	val &= 0xFF;
	if (val <= 0x20)
		REG_WR(sc, PXP2_REG_PGL_TAGS_LIMIT, 0x20);
}