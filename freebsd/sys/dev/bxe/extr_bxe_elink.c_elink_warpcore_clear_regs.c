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
struct elink_reg_set {int member_2; int val; scalar_t__ reg; int /*<<< orphan*/  const devad; int /*<<< orphan*/  member_1; int /*<<< orphan*/  const member_0; } ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct elink_reg_set*) ; 
#define  MDIO_AN_DEVAD 140 
#define  MDIO_AN_REG_CTRL 139 
#define  MDIO_WC_DEVAD 138 
#define  MDIO_WC_REG_COMBO_IEEE0_MIICTRL 137 
#define  MDIO_WC_REG_DIGITAL4_MISC3 136 
#define  MDIO_WC_REG_FX100_CTRL1 135 
#define  MDIO_WC_REG_FX100_CTRL3 134 
#define  MDIO_WC_REG_IEEE0BLK_MIICNTL 133 
 int /*<<< orphan*/  MDIO_WC_REG_RX66_CONTROL ; 
#define  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1 132 
#define  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2 131 
#define  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X3 130 
#define  MDIO_WC_REG_SERDESDIGITAL_MISC1 129 
 scalar_t__ MDIO_WC_REG_TX0_TX_DRIVER ; 
#define  MDIO_WC_REG_TX_FIR_TAP 128 
 int /*<<< orphan*/  elink_cl45_read_or_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/  const,scalar_t__,int) ; 
 size_t elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 

__attribute__((used)) static void elink_warpcore_clear_regs(struct elink_phy *phy,
				      struct elink_params *params,
				      uint16_t lane)
{
	struct bxe_softc *sc = params->sc;
	uint16_t i;
	static struct elink_reg_set wc_regs[] = {
		{MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0},
		{MDIO_WC_DEVAD, MDIO_WC_REG_FX100_CTRL1, 0x014a},
		{MDIO_WC_DEVAD, MDIO_WC_REG_FX100_CTRL3, 0x0800},
		{MDIO_WC_DEVAD, MDIO_WC_REG_DIGITAL4_MISC3, 0x8008},
		{MDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
			0x0195},
		{MDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			0x0007},
		{MDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X3,
			0x0002},
		{MDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_MISC1, 0x6000},
		{MDIO_WC_DEVAD, MDIO_WC_REG_TX_FIR_TAP, 0x0000},
		{MDIO_WC_DEVAD, MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x2040},
		{MDIO_WC_DEVAD, MDIO_WC_REG_COMBO_IEEE0_MIICTRL, 0x0140}
	};
	/* Set XFI clock comp as default. */
	elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_RX66_CONTROL, (3<<13));

	for (i = 0; i < ARRAY_SIZE(wc_regs); i++)
		elink_cl45_write(sc, phy, wc_regs[i].devad, wc_regs[i].reg,
				 wc_regs[i].val);

	lane = elink_get_warpcore_lane(phy, params);
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_TX0_TX_DRIVER + 0x10*lane, 0x0990);

}