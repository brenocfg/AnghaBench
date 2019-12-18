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
struct mtk_usb_phy_softc {int /*<<< orphan*/  u2_base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MT7621_U2_BASE_P1 ; 
 struct mtk_usb_phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_usb_phy_slew_rate_calibration (struct mtk_usb_phy_softc*) ; 

__attribute__((used)) static void
mtk_usb_phy_mt7621_init(device_t dev)
{
#ifdef notyet
	struct mtk_usb_phy_softc *sc = device_get_softc(dev);

	/* Slew rate calibration only, but for 2 ports */
	mtk_usb_phy_slew_rate_calibration(sc);

	sc->u2_base = MT7621_U2_BASE_P1;
	mtk_usb_phy_slew_rate_calibration(sc);
#endif
}