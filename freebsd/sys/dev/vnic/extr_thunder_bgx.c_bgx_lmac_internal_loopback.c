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
typedef  int /*<<< orphan*/  uint64_t ;
struct lmac {scalar_t__ is_sgmii; } ;
struct bgx {struct lmac* lmac; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_GMP_PCS_MRX_CTL ; 
 int /*<<< orphan*/  BGX_SPUX_CONTROL1 ; 
 int MAX_BGX_PER_CN88XX ; 
 int /*<<< orphan*/  PCS_MRX_CTL_LOOPBACK1 ; 
 int /*<<< orphan*/  SPU_CTL_LOOPBACK ; 
 int /*<<< orphan*/  bgx_reg_read (struct bgx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bgx** bgx_vnic ; 

void
bgx_lmac_internal_loopback(int node, int bgx_idx,
    int lmac_idx, boolean_t enable)
{
	struct bgx *bgx;
	struct lmac *lmac;
	uint64_t cfg;

	bgx = bgx_vnic[(node * MAX_BGX_PER_CN88XX) + bgx_idx];
	if (bgx == NULL)
		return;

	lmac = &bgx->lmac[lmac_idx];
	if (lmac->is_sgmii) {
		cfg = bgx_reg_read(bgx, lmac_idx, BGX_GMP_PCS_MRX_CTL);
		if (enable)
			cfg |= PCS_MRX_CTL_LOOPBACK1;
		else
			cfg &= ~PCS_MRX_CTL_LOOPBACK1;
		bgx_reg_write(bgx, lmac_idx, BGX_GMP_PCS_MRX_CTL, cfg);
	} else {
		cfg = bgx_reg_read(bgx, lmac_idx, BGX_SPUX_CONTROL1);
		if (enable)
			cfg |= SPU_CTL_LOOPBACK;
		else
			cfg &= ~SPU_CTL_LOOPBACK;
		bgx_reg_write(bgx, lmac_idx, BGX_SPUX_CONTROL1, cfg);
	}
}