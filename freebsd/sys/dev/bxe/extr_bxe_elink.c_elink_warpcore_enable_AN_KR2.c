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
typedef  size_t uint16_t ;
struct elink_vars {int dummy; } ;
struct elink_reg_set {int member_2; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; int /*<<< orphan*/  devad; int /*<<< orphan*/  member_1; int /*<<< orphan*/  const member_0; } ;
struct elink_phy {int dummy; } ;
struct elink_params {int /*<<< orphan*/  link_attr_sync; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct elink_reg_set*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  LINK_ATTR_SYNC_KR2_ENABLE ; 
#define  MDIO_WC_DEVAD 143 
 int /*<<< orphan*/  MDIO_WC_REG_CL49_USERB0_CTRL ; 
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
 int /*<<< orphan*/  elink_cl45_read_or_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_update_link_attr (struct elink_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_warpcore_enable_AN_KR2(struct elink_phy *phy,
					 struct elink_params *params,
					 struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint16_t i;
	static struct elink_reg_set reg_set[] = {
		/* Step 1 - Program the TX/RX alignment markers */
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL5, 0xa157},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL7, 0xcbe2},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL6, 0x7537},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL9, 0xa157},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL11, 0xcbe2},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL10, 0x7537},
		/* Step 2 - Configure the NP registers */
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_USERB0_CTRL, 0x000a},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL1, 0x6400},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL3, 0x0620},
		{MDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CODE_FIELD, 0x0157},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI1, 0x6464},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI2, 0x3150},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI3, 0x3150},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_BAM_CODE, 0x0157},
		{MDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_UD_CODE, 0x0620}
	};
	ELINK_DEBUG_P0(sc, "Enabling 20G-KR2\n");

	elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_CL49_USERB0_CTRL, (3<<6));

	for (i = 0; i < ARRAY_SIZE(reg_set); i++)
		elink_cl45_write(sc, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);

	/* Start KR2 work-around timer which handles BCM8073 link-parner */
	params->link_attr_sync |= LINK_ATTR_SYNC_KR2_ENABLE;
	elink_update_link_attr(params, params->link_attr_sync);
}