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
struct gsw_mt753x {int phy_base; int smi_addr; int (* mii_read ) (struct gsw_mt753x*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  port6_cfg; int /*<<< orphan*/  port5_cfg; int /*<<< orphan*/  (* mii_write ) (struct gsw_mt753x*,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  mmd_write; int /*<<< orphan*/  mmd_read; } ;

/* Variables and functions */
 int BMCR_ISOLATE ; 
 int FORCE_MODE_LNK ; 
 int /*<<< orphan*/  GMACCR ; 
 int MAX_RX_JUMBO_S ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MT753X_NUM_PHYS ; 
 int MT753X_SMI_ADDR_MASK ; 
 int MTCC_LMT_S ; 
 int /*<<< orphan*/  PMCR (int) ; 
 int RX_PKT_LEN_MAX_JUMBO ; 
 int /*<<< orphan*/  SMT0_IOLB ; 
 int SMT_IOLB_5_SMI_MDC_EN ; 
 int SW_REG_RST ; 
 int SW_SYS_RST ; 
 int /*<<< orphan*/  SYS_CTRL ; 
 int /*<<< orphan*/  mt7531_core_pll_setup (struct gsw_mt753x*) ; 
 int /*<<< orphan*/  mt7531_mac_port_setup (struct gsw_mt753x*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7531_set_gpio_pinmux (struct gsw_mt753x*) ; 
 int mt753x_mii_read (struct gsw_mt753x*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt753x_mii_write (struct gsw_mt753x*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt753x_mmd_read ; 
 int /*<<< orphan*/  mt753x_mmd_write ; 
 int mt753x_reg_read (struct gsw_mt753x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct gsw_mt753x*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct gsw_mt753x*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mt7531_sw_init(struct gsw_mt753x *gsw)
{
	int i;
	u32 val;

	gsw->phy_base = (gsw->smi_addr + 1) & MT753X_SMI_ADDR_MASK;

	gsw->mii_read = mt753x_mii_read;
	gsw->mii_write = mt753x_mii_write;
	gsw->mmd_read = mt753x_mmd_read;
	gsw->mmd_write = mt753x_mmd_write;

	for (i = 0; i < MT753X_NUM_PHYS; i++) {
		val = gsw->mii_read(gsw, i, MII_BMCR);
		val |= BMCR_ISOLATE;
		gsw->mii_write(gsw, i, MII_BMCR, val);
	}

	/* Force MAC link down before reset */
	mt753x_reg_write(gsw, PMCR(5), FORCE_MODE_LNK);
	mt753x_reg_write(gsw, PMCR(6), FORCE_MODE_LNK);

	/* Switch soft reset */
	mt753x_reg_write(gsw, SYS_CTRL, SW_SYS_RST | SW_REG_RST);
	usleep_range(10, 20);

	/* Enable MDC input Schmitt Trigger */
	val = mt753x_reg_read(gsw, SMT0_IOLB);
	mt753x_reg_write(gsw, SMT0_IOLB, val | SMT_IOLB_5_SMI_MDC_EN);

	/* Set 7531 gpio pinmux */
	mt7531_set_gpio_pinmux(gsw);

	/* Global mac control settings */
	mt753x_reg_write(gsw, GMACCR,
			 (15 << MTCC_LMT_S) | (11 << MAX_RX_JUMBO_S) |
			 RX_PKT_LEN_MAX_JUMBO);

	mt7531_core_pll_setup(gsw);
	mt7531_mac_port_setup(gsw, 5, &gsw->port5_cfg);
	mt7531_mac_port_setup(gsw, 6, &gsw->port6_cfg);

	return 0;
}