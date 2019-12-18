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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ PIN_CFG_EPIO0 ; 
 scalar_t__ PIN_CFG_GPIO0_P0 ; 
 scalar_t__ PIN_CFG_NA ; 
 int /*<<< orphan*/  elink_cb_gpio_write (struct bxe_softc*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  elink_set_epio (struct bxe_softc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void elink_set_cfg_pin(struct bxe_softc *sc, uint32_t pin_cfg, uint32_t val)
{
	if (pin_cfg == PIN_CFG_NA)
		return;
	if (pin_cfg >= PIN_CFG_EPIO0) {
		elink_set_epio(sc, pin_cfg - PIN_CFG_EPIO0, val);
	} else {
		uint8_t gpio_num = (pin_cfg - PIN_CFG_GPIO0_P0) & 0x3;
		uint8_t gpio_port = (pin_cfg - PIN_CFG_GPIO0_P0) >> 2;
		elink_cb_gpio_write(sc, gpio_num, (uint8_t)val, gpio_port);
	}
}