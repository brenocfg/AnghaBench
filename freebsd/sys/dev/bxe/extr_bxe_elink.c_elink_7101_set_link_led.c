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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
#define  ELINK_LED_MODE_FRONT_PANEL_OFF 131 
#define  ELINK_LED_MODE_OFF 130 
#define  ELINK_LED_MODE_ON 129 
#define  ELINK_LED_MODE_OPER 128 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7107_LINK_LED_CNTL ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void elink_7101_set_link_led(struct elink_phy *phy,
				    struct elink_params *params, uint8_t mode)
{
	uint16_t val = 0;
	struct bxe_softc *sc = params->sc;
	switch (mode) {
	case ELINK_LED_MODE_FRONT_PANEL_OFF:
	case ELINK_LED_MODE_OFF:
		val = 2;
		break;
	case ELINK_LED_MODE_ON:
		val = 1;
		break;
	case ELINK_LED_MODE_OPER:
		val = 0;
		break;
	}
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_7107_LINK_LED_CNTL,
			 val);
}