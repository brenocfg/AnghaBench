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
struct elink_vars {int /*<<< orphan*/  check_kr2_recovery_cnt; } ;
struct elink_reg_set {int member_2; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; int /*<<< orphan*/  devad; int /*<<< orphan*/  member_1; int /*<<< orphan*/  const member_0; } ;
struct elink_phy {int dummy; } ;
struct elink_params {int /*<<< orphan*/  link_attr_sync; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct elink_reg_set*) ; 
 int /*<<< orphan*/  ELINK_CHECK_KR2_RECOVERY_CNT ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  LINK_ATTR_SYNC_KR2_ENABLE ; 
#define  MDIO_WC_DEVAD 143 
#define  MDIO_WC_REG_CL73_BAM_CODE_FIELD 142 
#define  MDIO_WC_REG_CL73_BAM_CTRL1 141 
#define  MDIO_WC_REG_CL73_BAM_CTRL3 140 
#define  MDIO_WC_REG_CL73_USERB0_CTRL 139 
#define  MDIO_WC_REG_CL82_USERB1_RX_CTRL10 138 
#define  MDIO_WC_REG_CL82_USERB1_RX_CTRL11 137 
#define  MDIO_WC_REG_CL82_USERB1_TX_CTRL5 136 
#define  MDIO_WC_REG_CL82_USERB1_TX_CTRL6 135 
#define  MDIO_WC_REG_CL82_USERB1_TX_CTRL7 134 
#define  MDIO_WC_REG_CL82_USERB1_TX_CTRL9 133 
#define  MDIO_WC_REG_ETA_CL73_LD_BAM_CODE 132 
#define  MDIO_WC_REG_ETA_CL73_LD_UD_CODE 131 
#define  MDIO_WC_REG_ETA_CL73_OUI1 130 
#define  MDIO_WC_REG_ETA_CL73_OUI2 129 
#define  MDIO_WC_REG_ETA_CL73_OUI3 128 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_update_link_attr (struct elink_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_disable_kr2(struct elink_params *params,
			      struct elink_vars *vars,
			      struct elink_phy *phy)
{
	struct bxe_softc *sc = params->sc;
	int i;
	static struct elink_reg_set reg_set[] = {
		/* Step 1 - Program the TX/RX alignment markers */
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL5, 0x7690},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL7, 0xe647},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL6, 0xc4f0},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL9, 0x7690},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL11, 0xe647},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL10, 0xc4f0},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_USERB0_CTRL, 0x000c},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL1, 0x6000},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL3, 0x0000},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CODE_FIELD, 0x0002},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI1, 0x0000},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI2, 0x0af7},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI3, 0x0af7},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_BAM_CODE, 0x0002},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_UD_CODE, 0x0000}
	};
	ELINK_DEBUG_P0(sc, "Disabling 20G-KR2\n");

	for (i = 0; i < ARRAY_SIZE(reg_set); i++)
		elink_cl45_write(sc, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);
	params->link_attr_sync &= ~LINK_ATTR_SYNC_KR2_ENABLE;
	elink_update_link_attr(params, params->link_attr_sync);

	vars->check_kr2_recovery_cnt = ELINK_CHECK_KR2_RECOVERY_CNT;
}