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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
struct lmac {int /*<<< orphan*/ * phy_if_dev; int /*<<< orphan*/  phyaddr; int /*<<< orphan*/  check_link_mtx; int /*<<< orphan*/  check_link; } ;
struct bgx {scalar_t__ lmac_type; int /*<<< orphan*/  dev; struct lmac* lmac; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_CMRX_CFG ; 
 scalar_t__ BGX_MODE_10G_KR ; 
 scalar_t__ BGX_MODE_40G_KR ; 
 scalar_t__ BGX_MODE_XFI ; 
 scalar_t__ BGX_MODE_XLAUI ; 
 scalar_t__ LMAC_PHY_DISCONNECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bgx_flush_dmac_addrs (struct bgx*,size_t) ; 
 int bgx_reg_read (struct bgx*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bgx_lmac_disable(struct bgx *bgx, uint8_t lmacid)
{
	struct lmac *lmac;
	uint64_t cmrx_cfg;

	lmac = &bgx->lmac[lmacid];

	/* Stop callout */
	callout_drain(&lmac->check_link);
	mtx_destroy(&lmac->check_link_mtx);

	cmrx_cfg = bgx_reg_read(bgx, lmacid, BGX_CMRX_CFG);
	cmrx_cfg &= ~(1 << 15);
	bgx_reg_write(bgx, lmacid, BGX_CMRX_CFG, cmrx_cfg);
	bgx_flush_dmac_addrs(bgx, lmacid);

	if ((bgx->lmac_type != BGX_MODE_XFI) &&
	    (bgx->lmac_type != BGX_MODE_XLAUI) &&
	    (bgx->lmac_type != BGX_MODE_40G_KR) &&
	    (bgx->lmac_type != BGX_MODE_10G_KR)) {
		if (lmac->phy_if_dev == NULL) {
			device_printf(bgx->dev,
			    "LMAC%d missing interface to PHY\n", lmacid);
			return;
		}
		if (LMAC_PHY_DISCONNECT(lmac->phy_if_dev, lmac->phyaddr,
		    lmacid) != 0) {
			device_printf(bgx->dev,
			    "LMAC%d could not disconnect PHY\n", lmacid);
			return;
		}
		lmac->phy_if_dev = NULL;
	}
}