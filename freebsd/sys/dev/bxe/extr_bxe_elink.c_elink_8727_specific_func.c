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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct elink_phy {int flags; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
#define  ELINK_DISABLE_TX 130 
#define  ELINK_ENABLE_TX 129 
 int ELINK_FLAGS_NOC ; 
 int ELINK_FLAGS_SFP_NOT_APPROVED ; 
#define  ELINK_PHY_INIT 128 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXCTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_TXCTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_PCS_OPT_CTRL ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_sfp_set_transmitter (struct elink_params*,struct elink_phy*,int) ; 

__attribute__((used)) static void elink_8727_specific_func(struct elink_phy *phy,
				     struct elink_params *params,
				     uint32_t action)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val;
	switch (action) {
	case ELINK_DISABLE_TX:
		elink_sfp_set_transmitter(params, phy, 0);
		break;
	case ELINK_ENABLE_TX:
		if (!(phy->flags & ELINK_FLAGS_SFP_NOT_APPROVED))
			elink_sfp_set_transmitter(params, phy, 1);
		break;
	case ELINK_PHY_INIT:
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 (1<<2) | (1<<5));
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_TXCTRL,
				 0);
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x0006);
		/* Make MOD_ABS give interrupt on change */
		elink_cl45_read(sc, phy, MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8727_PCS_OPT_CTRL,
				&val);
		val |= (1<<12);
		if (phy->flags & ELINK_FLAGS_NOC)
			val |= (3<<5);
		/* Set 8727 GPIOs to input to allow reading from the 8727 GPIO0
		 * status which reflect SFP+ module over-current
		 */
		if (!(phy->flags & ELINK_FLAGS_NOC))
			val &= 0xff8f; /* Reset bits 4-6 */
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_PCS_OPT_CTRL,
				 val);
		break;
	default:
		ELINK_DEBUG_P1(sc, "Function 0x%x not supported by 8727\n",
		   action);
		return;
	}
}