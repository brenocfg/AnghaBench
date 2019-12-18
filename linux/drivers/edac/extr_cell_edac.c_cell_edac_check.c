#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mem_ctl_info {int /*<<< orphan*/  pdev; struct cell_edac_priv* pvt_info; } ;
struct cell_edac_priv {int prev_fir; int chanmask; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  mic_fir; int /*<<< orphan*/  mic_df_ecc_address_1; int /*<<< orphan*/  mic_df_ecc_address_0; } ;

/* Variables and functions */
 int CBE_MIC_FIR_ECC_ERR_MASK ; 
 int CBE_MIC_FIR_ECC_MULTI_0_ERR ; 
 int CBE_MIC_FIR_ECC_MULTI_0_RESET ; 
 int CBE_MIC_FIR_ECC_MULTI_1_ERR ; 
 int CBE_MIC_FIR_ECC_MULTI_1_RESET ; 
 int CBE_MIC_FIR_ECC_RESET_MASK ; 
 int CBE_MIC_FIR_ECC_SET_MASK ; 
 int CBE_MIC_FIR_ECC_SINGLE_0_ERR ; 
 int CBE_MIC_FIR_ECC_SINGLE_0_RESET ; 
 int CBE_MIC_FIR_ECC_SINGLE_1_ERR ; 
 int CBE_MIC_FIR_ECC_SINGLE_1_RESET ; 
 int /*<<< orphan*/  cell_edac_count_ce (struct mem_ctl_info*,int,int) ; 
 int /*<<< orphan*/  cell_edac_count_ue (struct mem_ctl_info*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int in_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  out_be64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cell_edac_check(struct mem_ctl_info *mci)
{
	struct cell_edac_priv		*priv = mci->pvt_info;
	u64				fir, addreg, clear = 0;

	fir = in_be64(&priv->regs->mic_fir);
#ifdef DEBUG
	if (fir != priv->prev_fir) {
		dev_dbg(mci->pdev, "fir change : 0x%016lx\n", fir);
		priv->prev_fir = fir;
	}
#endif
	if ((priv->chanmask & 0x1) && (fir & CBE_MIC_FIR_ECC_SINGLE_0_ERR)) {
		addreg = in_be64(&priv->regs->mic_df_ecc_address_0);
		clear |= CBE_MIC_FIR_ECC_SINGLE_0_RESET;
		cell_edac_count_ce(mci, 0, addreg);
	}
	if ((priv->chanmask & 0x2) && (fir & CBE_MIC_FIR_ECC_SINGLE_1_ERR)) {
		addreg = in_be64(&priv->regs->mic_df_ecc_address_1);
		clear |= CBE_MIC_FIR_ECC_SINGLE_1_RESET;
		cell_edac_count_ce(mci, 1, addreg);
	}
	if ((priv->chanmask & 0x1) && (fir & CBE_MIC_FIR_ECC_MULTI_0_ERR)) {
		addreg = in_be64(&priv->regs->mic_df_ecc_address_0);
		clear |= CBE_MIC_FIR_ECC_MULTI_0_RESET;
		cell_edac_count_ue(mci, 0, addreg);
	}
	if ((priv->chanmask & 0x2) && (fir & CBE_MIC_FIR_ECC_MULTI_1_ERR)) {
		addreg = in_be64(&priv->regs->mic_df_ecc_address_1);
		clear |= CBE_MIC_FIR_ECC_MULTI_1_RESET;
		cell_edac_count_ue(mci, 1, addreg);
	}

	/* The procedure for clearing FIR bits is a bit ... weird */
	if (clear) {
		fir &= ~(CBE_MIC_FIR_ECC_ERR_MASK | CBE_MIC_FIR_ECC_SET_MASK);
		fir |= CBE_MIC_FIR_ECC_RESET_MASK;
		fir &= ~clear;
		out_be64(&priv->regs->mic_fir, fir);
		(void)in_be64(&priv->regs->mic_fir);

		mb();	/* sync up */
#ifdef DEBUG
		fir = in_be64(&priv->regs->mic_fir);
		dev_dbg(mci->pdev, "fir clear  : 0x%016lx\n", fir);
#endif
	}
}