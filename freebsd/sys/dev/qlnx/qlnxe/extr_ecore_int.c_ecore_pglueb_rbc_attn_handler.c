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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int,...) ; 
 int ECORE_PGLUE_ATTENTION_DETAILS2_BME ; 
 int ECORE_PGLUE_ATTENTION_DETAILS2_FID_EN ; 
 int ECORE_PGLUE_ATTENTION_DETAILS2_WAS_ERR ; 
 int ECORE_PGLUE_ATTENTION_DETAILS_PFID_MASK ; 
 int ECORE_PGLUE_ATTENTION_DETAILS_PFID_SHIFT ; 
 int ECORE_PGLUE_ATTENTION_DETAILS_VFID_MASK ; 
 int ECORE_PGLUE_ATTENTION_DETAILS_VFID_SHIFT ; 
 int ECORE_PGLUE_ATTENTION_DETAILS_VF_VALID ; 
 int ECORE_PGLUE_ATTENTION_ICPL_VALID ; 
 int ECORE_PGLUE_ATTENTION_ILT_VALID ; 
 int ECORE_PGLUE_ATTENTION_RD_VALID ; 
 int ECORE_PGLUE_ATTENTION_VALID ; 
 int ECORE_PGLUE_ATTENTION_ZLR_VALID ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  PGLUE_B_REG_LATCHED_ERRORS_CLR ; 
 int /*<<< orphan*/  PGLUE_B_REG_MASTER_ZLR_ERR_ADD_31_0 ; 
 int /*<<< orphan*/  PGLUE_B_REG_MASTER_ZLR_ERR_ADD_63_32 ; 
 int /*<<< orphan*/  PGLUE_B_REG_MASTER_ZLR_ERR_DETAILS ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_RD_ADD_31_0 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_RD_ADD_63_32 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_RD_DETAILS ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_RD_DETAILS2 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_ADD_31_0 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_ADD_63_32 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_DETAILS ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_DETAILS2 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_DETAILS_ICPL ; 
 int /*<<< orphan*/  PGLUE_B_REG_VF_ILT_ERR_ADD_31_0 ; 
 int /*<<< orphan*/  PGLUE_B_REG_VF_ILT_ERR_ADD_63_32 ; 
 int /*<<< orphan*/  PGLUE_B_REG_VF_ILT_ERR_DETAILS ; 
 int /*<<< orphan*/  PGLUE_B_REG_VF_ILT_ERR_DETAILS2 ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_pglueb_rbc_attn_handler(struct ecore_hwfn *p_hwfn,
						   struct ecore_ptt *p_ptt)
{
	u32 tmp;

	tmp = ecore_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_WR_DETAILS2);
	if (tmp & ECORE_PGLUE_ATTENTION_VALID) {
		u32 addr_lo, addr_hi, details;

		addr_lo = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_TX_ERR_WR_ADD_31_0);
		addr_hi = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_TX_ERR_WR_ADD_63_32);
		details = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_TX_ERR_WR_DETAILS);

		DP_NOTICE(p_hwfn, false,
			  "Illegal write by chip to [%08x:%08x] blocked. Details: %08x [PFID %02x, VFID %02x, VF_VALID %02x] Details2 %08x [Was_error %02x BME deassert %02x FID_enable deassert %02x]\n",
			  addr_hi, addr_lo, details,
			  (u8)((details & ECORE_PGLUE_ATTENTION_DETAILS_PFID_MASK) >> ECORE_PGLUE_ATTENTION_DETAILS_PFID_SHIFT),
			  (u8)((details & ECORE_PGLUE_ATTENTION_DETAILS_VFID_MASK) >> ECORE_PGLUE_ATTENTION_DETAILS_VFID_SHIFT),
			  (u8)((details & ECORE_PGLUE_ATTENTION_DETAILS_VF_VALID) ? 1 : 0),
			  tmp,
			  (u8)((tmp & ECORE_PGLUE_ATTENTION_DETAILS2_WAS_ERR) ? 1 : 0),
			  (u8)((tmp & ECORE_PGLUE_ATTENTION_DETAILS2_BME) ? 1 : 0),
			  (u8)((tmp & ECORE_PGLUE_ATTENTION_DETAILS2_FID_EN) ? 1 : 0));
	}

	tmp = ecore_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_RD_DETAILS2);
	if (tmp & ECORE_PGLUE_ATTENTION_RD_VALID) {
		u32 addr_lo, addr_hi, details;

		addr_lo = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_TX_ERR_RD_ADD_31_0);
		addr_hi = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_TX_ERR_RD_ADD_63_32);
		details = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_TX_ERR_RD_DETAILS);

		DP_NOTICE(p_hwfn, false,
			  "Illegal read by chip from [%08x:%08x] blocked. Details: %08x [PFID %02x, VFID %02x, VF_VALID %02x] Details2 %08x [Was_error %02x BME deassert %02x FID_enable deassert %02x]\n",
			  addr_hi, addr_lo, details,
			  (u8)((details & ECORE_PGLUE_ATTENTION_DETAILS_PFID_MASK) >> ECORE_PGLUE_ATTENTION_DETAILS_PFID_SHIFT),
			  (u8)((details & ECORE_PGLUE_ATTENTION_DETAILS_VFID_MASK) >> ECORE_PGLUE_ATTENTION_DETAILS_VFID_SHIFT),
			  (u8)((details & ECORE_PGLUE_ATTENTION_DETAILS_VF_VALID) ? 1 : 0),
			  tmp,
			  (u8)((tmp & ECORE_PGLUE_ATTENTION_DETAILS2_WAS_ERR) ? 1 : 0),
			  (u8)((tmp & ECORE_PGLUE_ATTENTION_DETAILS2_BME) ? 1 : 0),
			  (u8)((tmp & ECORE_PGLUE_ATTENTION_DETAILS2_FID_EN) ? 1 : 0));
	}

	tmp = ecore_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_WR_DETAILS_ICPL);
	if (tmp & ECORE_PGLUE_ATTENTION_ICPL_VALID)
		DP_NOTICE(p_hwfn, false, "ICPL eror - %08x\n", tmp);

	tmp = ecore_rd(p_hwfn, p_ptt, PGLUE_B_REG_MASTER_ZLR_ERR_DETAILS);
	if (tmp & ECORE_PGLUE_ATTENTION_ZLR_VALID) {
		u32 addr_hi, addr_lo;

		addr_lo = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_MASTER_ZLR_ERR_ADD_31_0);
		addr_hi = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_MASTER_ZLR_ERR_ADD_63_32);

		DP_NOTICE(p_hwfn, false,
			  "ICPL eror - %08x [Address %08x:%08x]\n",
			  tmp, addr_hi, addr_lo);
	}

	tmp = ecore_rd(p_hwfn, p_ptt, PGLUE_B_REG_VF_ILT_ERR_DETAILS2);
	if (tmp & ECORE_PGLUE_ATTENTION_ILT_VALID) {
		u32 addr_hi, addr_lo, details;

		addr_lo = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_VF_ILT_ERR_ADD_31_0);
		addr_hi = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_VF_ILT_ERR_ADD_63_32);
		details = ecore_rd(p_hwfn, p_ptt,
				   PGLUE_B_REG_VF_ILT_ERR_DETAILS);

		DP_NOTICE(p_hwfn, false,
			  "ILT error - Details %08x Details2 %08x [Address %08x:%08x]\n",
			  details, tmp, addr_hi, addr_lo);
	}

	/* Clear the indications */
	ecore_wr(p_hwfn, p_ptt, PGLUE_B_REG_LATCHED_ERRORS_CLR, (1 << 2));

	return ECORE_SUCCESS;
}