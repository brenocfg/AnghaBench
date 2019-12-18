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
typedef  int u32 ;
struct adapter {int pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_INT_ENABLE ; 
 int /*<<< orphan*/  A_PL_INT_MAP0 ; 
 int /*<<< orphan*/  A_PL_PF_INT_ENABLE ; 
 int /*<<< orphan*/  A_SGE_INT_ENABLE3 ; 
 scalar_t__ CHELSIO_T5 ; 
 int F_DBFIFO_HP_INT ; 
 int F_DBFIFO_LP_INT ; 
 int F_EGRESS_SIZE_ERR ; 
 int F_ERR_BAD_DB_PIDX0 ; 
 int F_ERR_BAD_DB_PIDX1 ; 
 int F_ERR_BAD_DB_PIDX2 ; 
 int F_ERR_BAD_DB_PIDX3 ; 
 int F_ERR_CPL_EXCEED_IQE_SIZE ; 
 int F_ERR_CPL_OPCODE_0 ; 
 int F_ERR_DATA_CPL_ON_HIGH_QID0 ; 
 int F_ERR_DATA_CPL_ON_HIGH_QID1 ; 
 int F_ERR_DROPPED_DB ; 
 int F_ERR_EGR_CTXT_PRIO ; 
 int F_ERR_ING_CTXT_PRIO ; 
 int F_ERR_INVALID_CIDX_INC ; 
 int F_ERR_PCIE_ERROR0 ; 
 int F_ERR_PCIE_ERROR1 ; 
 int F_FATAL_WRE_LEN ; 
 int F_I2CM ; 
 int F_INGRESS_SIZE_ERR ; 
 int F_SF ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_INTR_MASK ; 
 scalar_t__ chip_id (struct adapter*) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t4_intr_enable(struct adapter *adap)
{
	u32 val = 0;

	if (chip_id(adap) <= CHELSIO_T5)
		val = F_ERR_DROPPED_DB | F_ERR_EGR_CTXT_PRIO | F_DBFIFO_HP_INT;
	else
		val = F_ERR_PCIE_ERROR0 | F_ERR_PCIE_ERROR1 | F_FATAL_WRE_LEN;
	val |= F_ERR_CPL_EXCEED_IQE_SIZE | F_ERR_INVALID_CIDX_INC |
	    F_ERR_CPL_OPCODE_0 | F_ERR_DATA_CPL_ON_HIGH_QID1 |
	    F_INGRESS_SIZE_ERR | F_ERR_DATA_CPL_ON_HIGH_QID0 |
	    F_ERR_BAD_DB_PIDX3 | F_ERR_BAD_DB_PIDX2 | F_ERR_BAD_DB_PIDX1 |
	    F_ERR_BAD_DB_PIDX0 | F_ERR_ING_CTXT_PRIO | F_DBFIFO_LP_INT |
	    F_EGRESS_SIZE_ERR;
	t4_set_reg_field(adap, A_SGE_INT_ENABLE3, val, val);
	t4_write_reg(adap, MYPF_REG(A_PL_PF_INT_ENABLE), PF_INTR_MASK);
	t4_set_reg_field(adap, A_PL_INT_ENABLE, F_SF | F_I2CM, 0);
	t4_set_reg_field(adap, A_PL_INT_MAP0, 0, 1 << adap->pf);
}