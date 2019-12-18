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
typedef  scalar_t__ usb_error_t ;
typedef  int uint32_t ;
struct urtw_softc {int /*<<< orphan*/  sc_gpio_ledpin; int /*<<< orphan*/  sc_strategy; int /*<<< orphan*/  sc_psr; } ;

/* Variables and functions */
#define  URTW_EPROM_CID_ALPHA0 132 
#define  URTW_EPROM_CID_HW_LED 131 
 int URTW_EPROM_CID_MASK ; 
#define  URTW_EPROM_CID_RSVD0 130 
#define  URTW_EPROM_CID_RSVD1 129 
#define  URTW_EPROM_CID_SERCOMM_PS 128 
 int /*<<< orphan*/  URTW_EPROM_SWREV ; 
 int /*<<< orphan*/  URTW_HW_LED ; 
 int /*<<< orphan*/  URTW_LED_PIN_GPIO0 ; 
 int /*<<< orphan*/  URTW_PSR ; 
 int /*<<< orphan*/  URTW_SW_LED_MODE0 ; 
 int /*<<< orphan*/  URTW_SW_LED_MODE1 ; 
 int /*<<< orphan*/  URTW_SW_LED_MODE3 ; 
 scalar_t__ urtw_eprom_read32 (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static usb_error_t
urtw_led_init(struct urtw_softc *sc)
{
	uint32_t rev;
	usb_error_t error;

	urtw_read8_m(sc, URTW_PSR, &sc->sc_psr);
	error = urtw_eprom_read32(sc, URTW_EPROM_SWREV, &rev);
	if (error != 0)
		goto fail;

	switch (rev & URTW_EPROM_CID_MASK) {
	case URTW_EPROM_CID_ALPHA0:
		sc->sc_strategy = URTW_SW_LED_MODE1;
		break;
	case URTW_EPROM_CID_SERCOMM_PS:
		sc->sc_strategy = URTW_SW_LED_MODE3;
		break;
	case URTW_EPROM_CID_HW_LED:
		sc->sc_strategy = URTW_HW_LED;
		break;
	case URTW_EPROM_CID_RSVD0:
	case URTW_EPROM_CID_RSVD1:
	default:
		sc->sc_strategy = URTW_SW_LED_MODE0;
		break;
	}

	sc->sc_gpio_ledpin = URTW_LED_PIN_GPIO0;

fail:
	return (error);
}