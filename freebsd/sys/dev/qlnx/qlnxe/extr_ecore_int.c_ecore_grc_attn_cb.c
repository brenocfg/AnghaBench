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
struct ecore_hwfn {int /*<<< orphan*/  p_dpc_ptt; int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,int,char*,int,int,char*,int,int /*<<< orphan*/ ,int,char*,int) ; 
 int ECORE_GRC_ATTENTION_ADDRESS_MASK ; 
 int ECORE_GRC_ATTENTION_MASTER_MASK ; 
 int ECORE_GRC_ATTENTION_MASTER_SHIFT ; 
 int ECORE_GRC_ATTENTION_PF_MASK ; 
 int ECORE_GRC_ATTENTION_PRIV_MASK ; 
 int ECORE_GRC_ATTENTION_PRIV_SHIFT ; 
 int ECORE_GRC_ATTENTION_PRIV_VF ; 
 int ECORE_GRC_ATTENTION_RDWR_BIT ; 
 int ECORE_GRC_ATTENTION_VALID_BIT ; 
 int ECORE_GRC_ATTENTION_VF_MASK ; 
 int ECORE_GRC_ATTENTION_VF_SHIFT ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_0 ; 
 int /*<<< orphan*/  GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_1 ; 
 int /*<<< orphan*/  GRC_REG_TIMEOUT_ATTN_ACCESS_VALID ; 
 int ecore_rd (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grc_timeout_attn_master_to_str (int) ; 

__attribute__((used)) static enum _ecore_status_t ecore_grc_attn_cb(struct ecore_hwfn *p_hwfn)
{
	u32 tmp, tmp2;

	/* We've already cleared the timeout interrupt register, so we learn
	 * of interrupts via the validity register
	 */
	tmp = ecore_rd(p_hwfn, p_hwfn->p_dpc_ptt,
		       GRC_REG_TIMEOUT_ATTN_ACCESS_VALID);
	if (!(tmp & ECORE_GRC_ATTENTION_VALID_BIT))
		goto out;

	/* Read the GRC timeout information */
	tmp = ecore_rd(p_hwfn, p_hwfn->p_dpc_ptt,
		       GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_0);
	tmp2 = ecore_rd(p_hwfn, p_hwfn->p_dpc_ptt,
			GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_1);

	DP_NOTICE(p_hwfn->p_dev, false,
		  "GRC timeout [%08x:%08x] - %s Address [%08x] [Master %s] [PF: %02x %s %02x]\n",
		  tmp2, tmp,
		  (tmp & ECORE_GRC_ATTENTION_RDWR_BIT) ? "Write to"
						       : "Read from",
		  (tmp & ECORE_GRC_ATTENTION_ADDRESS_MASK) << 2,
		  grc_timeout_attn_master_to_str((tmp & ECORE_GRC_ATTENTION_MASTER_MASK) >>
						 ECORE_GRC_ATTENTION_MASTER_SHIFT),
		  (tmp2 & ECORE_GRC_ATTENTION_PF_MASK),
		  (((tmp2 & ECORE_GRC_ATTENTION_PRIV_MASK) >>
		  ECORE_GRC_ATTENTION_PRIV_SHIFT) ==
		  ECORE_GRC_ATTENTION_PRIV_VF) ? "VF" : "(Irrelevant:)",
		  (tmp2 & ECORE_GRC_ATTENTION_VF_MASK) >>
		  ECORE_GRC_ATTENTION_VF_SHIFT);

out:
	/* Regardles of anything else, clean the validity bit */
	ecore_wr(p_hwfn, p_hwfn->p_dpc_ptt,
		 GRC_REG_TIMEOUT_ATTN_ACCESS_VALID, 0);
	return ECORE_SUCCESS;
}