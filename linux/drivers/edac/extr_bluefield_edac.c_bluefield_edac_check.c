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
typedef  scalar_t__ u32 ;
struct mem_ctl_info {scalar_t__ edac_cap; struct bluefield_edac_priv* pvt_info; } ;
struct bluefield_edac_priv {scalar_t__ emi_base; } ;

/* Variables and functions */
 scalar_t__ EDAC_FLAG_NONE ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MLXBF_ECC_CNT ; 
 int /*<<< orphan*/  MLXBF_ECC_CNT__DERR_CNT ; 
 int /*<<< orphan*/  MLXBF_ECC_CNT__SERR_CNT ; 
 scalar_t__ MLXBF_ECC_ERR ; 
 scalar_t__ MLXBF_ECC_ERR__DECC ; 
 scalar_t__ MLXBF_ECC_ERR__SECC ; 
 int /*<<< orphan*/  bluefield_gather_report_ecc (struct mem_ctl_info*,scalar_t__,int) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void bluefield_edac_check(struct mem_ctl_info *mci)
{
	struct bluefield_edac_priv *priv = mci->pvt_info;
	u32 ecc_count, single_error_count, double_error_count, ecc_error = 0;

	/*
	 * The memory controller might not be initialized by the firmware
	 * when there isn't memory, which may lead to bad register readings.
	 */
	if (mci->edac_cap == EDAC_FLAG_NONE)
		return;

	ecc_count = readl(priv->emi_base + MLXBF_ECC_CNT);
	single_error_count = FIELD_GET(MLXBF_ECC_CNT__SERR_CNT, ecc_count);
	double_error_count = FIELD_GET(MLXBF_ECC_CNT__DERR_CNT, ecc_count);

	if (single_error_count) {
		ecc_error |= MLXBF_ECC_ERR__SECC;

		bluefield_gather_report_ecc(mci, single_error_count, 1);
	}

	if (double_error_count) {
		ecc_error |= MLXBF_ECC_ERR__DECC;

		bluefield_gather_report_ecc(mci, double_error_count, 0);
	}

	/* Write to clear reported errors. */
	if (ecc_count)
		writel(ecc_error, priv->emi_base + MLXBF_ECC_ERR);
}