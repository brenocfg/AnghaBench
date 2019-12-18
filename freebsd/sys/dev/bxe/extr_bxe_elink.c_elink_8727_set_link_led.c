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
struct elink_phy {int flags; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ELINK_FLAGS_NOC ; 
#define  ELINK_LED_MODE_FRONT_PANEL_OFF 131 
#define  ELINK_LED_MODE_OFF 130 
#define  ELINK_LED_MODE_ON 129 
#define  ELINK_LED_MODE_OPER 128 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_GPIO_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_PCS_OPT_CTRL ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void elink_8727_set_link_led(struct elink_phy *phy,
				    struct elink_params *params, uint8_t mode)
{
	struct bxe_softc *sc = params->sc;
	uint16_t led_mode_bitmask = 0;
	uint16_t gpio_pins_bitmask = 0;
	uint16_t val;
	/* Only NOC flavor requires to set the LED specifically */
	if (!(phy->flags & ELINK_FLAGS_NOC))
		return;
	switch (mode) {
	case ELINK_LED_MODE_FRONT_PANEL_OFF:
	case ELINK_LED_MODE_OFF:
		led_mode_bitmask = 0;
		gpio_pins_bitmask = 0x03;
		break;
	case ELINK_LED_MODE_ON:
		led_mode_bitmask = 0;
		gpio_pins_bitmask = 0x02;
		break;
	case ELINK_LED_MODE_OPER:
		led_mode_bitmask = 0x60;
		gpio_pins_bitmask = 0x11;
		break;
	}
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8727_PCS_OPT_CTRL,
			&val);
	val &= 0xff8f;
	val |= led_mode_bitmask;
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_PCS_OPT_CTRL,
			 val);
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8727_GPIO_CTRL,
			&val);
	val &= 0xffe0;
	val |= gpio_pins_bitmask;
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_GPIO_CTRL,
			 val);
}