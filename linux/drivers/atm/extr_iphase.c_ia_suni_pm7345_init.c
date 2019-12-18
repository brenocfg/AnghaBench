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
struct iadev_priv {int phy_type; } ;
struct ia_reg {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  suni_rxcp_intr_en_sts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ia_reg const*) ; 
 int FE_DS3_PHY ; 
 int /*<<< orphan*/  SUNI_CONFIG ; 
#define  SUNI_ID_RESET 151 
#define  SUNI_INTR_ENBL 150 
#define  SUNI_MASTER_TEST 149 
 int /*<<< orphan*/  SUNI_OOCDE ; 
 int SUNI_PM7345_CLB ; 
 int SUNI_PM7345_DLB ; 
 int SUNI_PM7345_LLB ; 
 int SUNI_PM7345_PLB ; 
#define  SUNI_RXCP_CELL_MASK_H1 148 
#define  SUNI_RXCP_CELL_MASK_H2 147 
#define  SUNI_RXCP_CELL_MASK_H3 146 
#define  SUNI_RXCP_CELL_MASK_H4 145 
#define  SUNI_RXCP_CELL_PAT_H1 144 
#define  SUNI_RXCP_CELL_PAT_H2 143 
#define  SUNI_RXCP_CELL_PAT_H3 142 
#define  SUNI_RXCP_CELL_PAT_H4 141 
#define  SUNI_RXCP_CTRL 140 
#define  SUNI_RXCP_FCTRL 139 
#define  SUNI_RXCP_IDLE_MASK_H1 138 
#define  SUNI_RXCP_IDLE_MASK_H2 137 
#define  SUNI_RXCP_IDLE_MASK_H3 136 
#define  SUNI_RXCP_IDLE_MASK_H4 135 
#define  SUNI_RXCP_IDLE_PAT_H1 134 
#define  SUNI_RXCP_IDLE_PAT_H2 133 
#define  SUNI_RXCP_IDLE_PAT_H3 132 
#define  SUNI_RXCP_IDLE_PAT_H4 131 
#define  SUNI_TXCP_CTRL 130 
#define  SUNI_TXCP_IDLE_PAT_H5 129 
#define  SUNI_TXCP_INTR_EN_STS 128 
 int ia_phy_read32 (struct iadev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia_phy_write (struct iadev_priv*,struct ia_reg const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia_phy_write32 (struct iadev_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ia_suni_pm7345_init_ds3 (struct iadev_priv*) ; 
 int /*<<< orphan*/  ia_suni_pm7345_init_e3 (struct iadev_priv*) ; 
 TYPE_1__* suni_pm7345 ; 

__attribute__((used)) static void ia_suni_pm7345_init(struct iadev_priv *iadev)
{
	static const struct ia_reg suni_init[] = {
		/* Enable RSOP loss of signal interrupt. */
		{ SUNI_INTR_ENBL,		0x28 },
		/* Clear error counters. */
		{ SUNI_ID_RESET,		0 },
		/* Clear "PMCTST" in master test register. */
		{ SUNI_MASTER_TEST,		0 },

		{ SUNI_RXCP_CTRL,		0x2c },
		{ SUNI_RXCP_FCTRL,		0x81 },

		{ SUNI_RXCP_IDLE_PAT_H1,	0 },
		{ SUNI_RXCP_IDLE_PAT_H2,	0 },
		{ SUNI_RXCP_IDLE_PAT_H3,	0 },
		{ SUNI_RXCP_IDLE_PAT_H4,	0x01 },

		{ SUNI_RXCP_IDLE_MASK_H1,	0xff },
		{ SUNI_RXCP_IDLE_MASK_H2,	0xff },
		{ SUNI_RXCP_IDLE_MASK_H3,	0xff },
		{ SUNI_RXCP_IDLE_MASK_H4,	0xfe },

		{ SUNI_RXCP_CELL_PAT_H1,	0 },
		{ SUNI_RXCP_CELL_PAT_H2,	0 },
		{ SUNI_RXCP_CELL_PAT_H3,	0 },
		{ SUNI_RXCP_CELL_PAT_H4,	0x01 },

		{ SUNI_RXCP_CELL_MASK_H1,	0xff },
		{ SUNI_RXCP_CELL_MASK_H2,	0xff },
		{ SUNI_RXCP_CELL_MASK_H3,	0xff },
		{ SUNI_RXCP_CELL_MASK_H4,	0xff },

		{ SUNI_TXCP_CTRL,		0xa4 },
		{ SUNI_TXCP_INTR_EN_STS,	0x10 },
		{ SUNI_TXCP_IDLE_PAT_H5,	0x55 }
	};

	if (iadev->phy_type & FE_DS3_PHY)
		ia_suni_pm7345_init_ds3(iadev);
	else
		ia_suni_pm7345_init_e3(iadev);

	ia_phy_write(iadev, suni_init, ARRAY_SIZE(suni_init));

	ia_phy_write32(iadev, SUNI_CONFIG, ia_phy_read32(iadev, SUNI_CONFIG) &
		~(SUNI_PM7345_LLB | SUNI_PM7345_CLB |
		  SUNI_PM7345_DLB | SUNI_PM7345_PLB));
#ifdef __SNMP__
   suni_pm7345->suni_rxcp_intr_en_sts |= SUNI_OOCDE;
#endif /* __SNMP__ */
   return;
}