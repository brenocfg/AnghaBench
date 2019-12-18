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
struct xgene_edac_pmd_ctx {unsigned int pmd; int /*<<< orphan*/  edac; } ;
struct edac_device_ctl_info {struct xgene_edac_pmd_ctx* pvt_info; } ;

/* Variables and functions */
 int MAX_CPU_PER_PMD ; 
 int /*<<< orphan*/  PCPHPERRINTSTS ; 
 unsigned int PMD0_MERR_MASK ; 
 int /*<<< orphan*/  xgene_edac_pcp_rd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  xgene_edac_pmd_l1_check (struct edac_device_ctl_info*,int) ; 
 int /*<<< orphan*/  xgene_edac_pmd_l2_check (struct edac_device_ctl_info*) ; 

__attribute__((used)) static void xgene_edac_pmd_check(struct edac_device_ctl_info *edac_dev)
{
	struct xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	unsigned int pcp_hp_stat;
	int i;

	xgene_edac_pcp_rd(ctx->edac, PCPHPERRINTSTS, &pcp_hp_stat);
	if (!((PMD0_MERR_MASK << ctx->pmd) & pcp_hp_stat))
		return;

	/* Check CPU L1 error */
	for (i = 0; i < MAX_CPU_PER_PMD; i++)
		xgene_edac_pmd_l1_check(edac_dev, i);

	/* Check CPU L2 error */
	xgene_edac_pmd_l2_check(edac_dev);
}