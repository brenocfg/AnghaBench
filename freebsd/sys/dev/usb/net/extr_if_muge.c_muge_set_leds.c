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
struct usb_ether {int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; } ;
struct muge_softc {int sc_leds; int sc_led_modes; int sc_led_modes_mask; } ;
typedef  int ssize_t ;
typedef  int phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  modes ;

/* Variables and functions */
 int ETH_HW_CFG_LED1_EN_ ; 
 int ETH_HW_CFG_LED2_EN_ ; 
 int ETH_HW_CFG_LED3_EN_ ; 
 int ETH_HW_CFG_LEDO_EN_ ; 
 int OF_getencprop (int,char*,int*,int) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*) ; 
 struct muge_softc* uether_getsc (struct usb_ether*) ; 
 int usb_fdt_get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
muge_set_leds(struct usb_ether *ue)
{
#ifdef FDT
	struct muge_softc *sc = uether_getsc(ue);
	phandle_t node;
	pcell_t modes[4];	/* 4 LEDs are possible */
	ssize_t proplen;
	uint32_t count;

	if ((node = usb_fdt_get_node(ue->ue_dev, ue->ue_udev)) != -1 &&
	    (proplen = OF_getencprop(node, "microchip,led-modes", modes,
	    sizeof(modes))) > 0) {
		count = proplen / sizeof( uint32_t );
		sc->sc_leds = (count > 0) * ETH_HW_CFG_LEDO_EN_ |
			      (count > 1) * ETH_HW_CFG_LED1_EN_ |
			      (count > 2) * ETH_HW_CFG_LED2_EN_ |
			      (count > 3) * ETH_HW_CFG_LED3_EN_;
		while (count-- > 0) {
			sc->sc_led_modes |= (modes[count] & 0xf) << (4 * count);
			sc->sc_led_modes_mask |= 0xf << (4 * count);
		}
		muge_dbg_printf(sc, "LED modes set from FDT data\n");
	}
#endif
}