#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cfg_tgtid_0; } ;
struct TYPE_4__ {TYPE_1__ tgtid; } ;
struct unit_regs {TYPE_2__ gen; } ;
struct al_udma_gen_tgtid_msix_conf {scalar_t__ sel; scalar_t__ access_en; } ;

/* Variables and functions */
 int UDMA_GEN_TGTID_CFG_TGTID_0_MSIX_TGTID_ACCESS_EN ; 
 int UDMA_GEN_TGTID_CFG_TGTID_0_MSIX_TGTID_SEL ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int) ; 

void al_udma_gen_tgtid_msix_conf_set(
	struct unit_regs			*unit_regs,
	struct al_udma_gen_tgtid_msix_conf	*conf)
{
	al_reg_write32_masked(
		&unit_regs->gen.tgtid.cfg_tgtid_0,
		UDMA_GEN_TGTID_CFG_TGTID_0_MSIX_TGTID_ACCESS_EN |
		UDMA_GEN_TGTID_CFG_TGTID_0_MSIX_TGTID_SEL,
		(conf->access_en ? UDMA_GEN_TGTID_CFG_TGTID_0_MSIX_TGTID_ACCESS_EN : 0) |
		(conf->sel ? UDMA_GEN_TGTID_CFG_TGTID_0_MSIX_TGTID_SEL : 0));
}