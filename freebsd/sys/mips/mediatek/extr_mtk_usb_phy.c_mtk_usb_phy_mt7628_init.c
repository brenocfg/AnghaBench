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
struct mtk_usb_phy_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  U2_PHY_AC0 ; 
 int /*<<< orphan*/  U2_PHY_AC1 ; 
 int /*<<< orphan*/  U2_PHY_ACR3 ; 
 int /*<<< orphan*/  U2_PHY_DCR0 ; 
 int /*<<< orphan*/  U2_PHY_DTM0 ; 
 int /*<<< orphan*/  USB_PHY_BARRIER (struct mtk_usb_phy_softc*) ; 
 int /*<<< orphan*/  USB_PHY_WRITE_U2 (struct mtk_usb_phy_softc*,int /*<<< orphan*/ ,int) ; 
 struct mtk_usb_phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_usb_phy_slew_rate_calibration (struct mtk_usb_phy_softc*) ; 

__attribute__((used)) static void
mtk_usb_phy_mt7628_init(device_t dev)
{
	struct mtk_usb_phy_softc *sc = device_get_softc(dev);

	/* XXX: possibly add barriers between the next writes? */
	USB_PHY_WRITE_U2(sc, U2_PHY_DCR0, 0x00ffff02);
	USB_PHY_BARRIER(sc);
	USB_PHY_WRITE_U2(sc, U2_PHY_DCR0, 0x00555502);
	USB_PHY_BARRIER(sc);
	USB_PHY_WRITE_U2(sc, U2_PHY_DCR0, 0x00aaaa02);
	USB_PHY_BARRIER(sc);
	USB_PHY_WRITE_U2(sc, U2_PHY_DCR0, 0x00000402);
	USB_PHY_BARRIER(sc);
	USB_PHY_WRITE_U2(sc,  U2_PHY_AC0, 0x0048086a);
	USB_PHY_BARRIER(sc);
	USB_PHY_WRITE_U2(sc,  U2_PHY_AC1, 0x4400001c);
	USB_PHY_BARRIER(sc);
	USB_PHY_WRITE_U2(sc, U2_PHY_ACR3, 0xc0200000);
	USB_PHY_BARRIER(sc);
	USB_PHY_WRITE_U2(sc, U2_PHY_DTM0, 0x02000000);
	USB_PHY_BARRIER(sc);

#ifdef notyet
	/* Slew rate calibration */
	mtk_usb_phy_slew_rate_calibration(sc);
#endif
}