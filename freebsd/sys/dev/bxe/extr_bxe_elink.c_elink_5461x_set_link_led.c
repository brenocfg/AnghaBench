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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
#define  ELINK_LED_MODE_FRONT_PANEL_OFF 131 
#define  ELINK_LED_MODE_OFF 130 
#define  ELINK_LED_MODE_ON 129 
#define  ELINK_LED_MODE_OPER 128 
 int /*<<< orphan*/  MDIO_REG_GPHY_SHADOW ; 
 int MDIO_REG_GPHY_SHADOW_LED_SEL1 ; 
 int MDIO_REG_GPHY_SHADOW_WR_ENA ; 
 int /*<<< orphan*/  elink_cl22_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl22_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void elink_5461x_set_link_led(struct elink_phy *phy,
				       struct elink_params *params, uint8_t mode)
{
	struct bxe_softc *sc = params->sc;
	uint16_t temp;

	elink_cl22_write(sc, phy,
		MDIO_REG_GPHY_SHADOW,
		MDIO_REG_GPHY_SHADOW_LED_SEL1);
	elink_cl22_read(sc, phy,
		MDIO_REG_GPHY_SHADOW,
		&temp);
	temp &= 0xff00;

	ELINK_DEBUG_P1(sc, "54618x set link led (mode=%x)\n", mode);
	switch (mode) {
	case ELINK_LED_MODE_FRONT_PANEL_OFF:
	case ELINK_LED_MODE_OFF:
		temp |= 0x00ee;
		break;
	case ELINK_LED_MODE_OPER:
		temp |= 0x0001;
		break;
	case ELINK_LED_MODE_ON:
		temp |= 0x00ff;
		break;
	default:
		break;
	}
	elink_cl22_write(sc, phy,
		MDIO_REG_GPHY_SHADOW,
		MDIO_REG_GPHY_SHADOW_WR_ENA | temp);
	return;
}