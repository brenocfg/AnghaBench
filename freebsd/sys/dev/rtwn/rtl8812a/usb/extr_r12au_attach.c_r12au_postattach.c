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
struct rtwn_usb_softc {int /*<<< orphan*/  uc_udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ic_ioctl; } ;
struct rtwn_softc {TYPE_1__ sc_ic; int /*<<< orphan*/ * mac_prog; int /*<<< orphan*/  sc_set_led; int /*<<< orphan*/  sc_rf_read; struct r12a_softc* sc_priv; } ;
struct r12a_softc {int ac_usb_dma_size; int ac_usb_dma_time; int chip; scalar_t__ board_type; scalar_t__ ext_lna_5g; scalar_t__ ext_pa_5g; scalar_t__ ext_lna_2g; scalar_t__ ext_pa_2g; } ;

/* Variables and functions */
 int R12A_CHIP_C_CUT ; 
 scalar_t__ R92C_BOARD_TYPE_COMBO ; 
 scalar_t__ R92C_BOARD_TYPE_MINICARD ; 
 scalar_t__ R92C_BOARD_TYPE_SOLO ; 
 struct rtwn_usb_softc* RTWN_USB_SOFTC (struct rtwn_softc*) ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int /*<<< orphan*/  r12a_c_cut_rf_read ; 
 int /*<<< orphan*/  r12a_ioctl_net ; 
 int /*<<< orphan*/  r12a_rf_read ; 
 int /*<<< orphan*/  r12a_set_led ; 
 int /*<<< orphan*/  r88e_set_led ; 
 int /*<<< orphan*/ * rtl8812au_mac_no_ext_pa_lna ; 
 scalar_t__ usbd_get_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r12au_postattach(struct rtwn_softc *sc)
{
	struct rtwn_usb_softc *uc = RTWN_USB_SOFTC(sc);
	struct r12a_softc *rs = sc->sc_priv;

	if (usbd_get_speed(uc->uc_udev) == USB_SPEED_SUPER) {
		rs->ac_usb_dma_size = 0x07;
		rs->ac_usb_dma_time = 0x1a;
	} else {
		rs->ac_usb_dma_size = 0x01;
		rs->ac_usb_dma_time = 0x10;
	}

	if (rs->chip & R12A_CHIP_C_CUT)
		sc->sc_rf_read = r12a_c_cut_rf_read;
	else
		sc->sc_rf_read = r12a_rf_read;

	if (rs->board_type == R92C_BOARD_TYPE_MINICARD ||
	    rs->board_type == R92C_BOARD_TYPE_SOLO ||
	    rs->board_type == R92C_BOARD_TYPE_COMBO)
		sc->sc_set_led = r88e_set_led;
	else
		sc->sc_set_led = r12a_set_led;

	if (!(rs->ext_pa_2g || rs->ext_lna_2g ||
	    rs->ext_pa_5g || rs->ext_lna_5g))
		sc->mac_prog = &rtl8812au_mac_no_ext_pa_lna[0];

	sc->sc_ic.ic_ioctl = r12a_ioctl_net;
}