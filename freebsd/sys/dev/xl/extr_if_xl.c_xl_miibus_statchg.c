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
struct xl_softc {scalar_t__ xl_type; int /*<<< orphan*/  xl_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media_active; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_1 (struct xl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct xl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XL_MACCTRL_DUPLEX ; 
 int /*<<< orphan*/  XL_MACCTRL_FLOW_CONTROL_ENB ; 
 int /*<<< orphan*/  XL_SEL_WIN (int) ; 
 scalar_t__ XL_TYPE_905B ; 
 int /*<<< orphan*/  XL_W3_MAC_CTRL ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xl_setcfg (struct xl_softc*) ; 

__attribute__((used)) static void
xl_miibus_statchg(device_t dev)
{
	struct xl_softc		*sc;
	struct mii_data		*mii;
	uint8_t			macctl;

	sc = device_get_softc(dev);
	mii = device_get_softc(sc->xl_miibus);

	xl_setcfg(sc);

	/* Set ASIC's duplex mode to match the PHY. */
	XL_SEL_WIN(3);
	macctl = CSR_READ_1(sc, XL_W3_MAC_CTRL);
	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
		macctl |= XL_MACCTRL_DUPLEX;
		if (sc->xl_type == XL_TYPE_905B) {
			if ((IFM_OPTIONS(mii->mii_media_active) &
			    IFM_ETH_RXPAUSE) != 0)
				macctl |= XL_MACCTRL_FLOW_CONTROL_ENB;
			else
				macctl &= ~XL_MACCTRL_FLOW_CONTROL_ENB;
		}
	} else {
		macctl &= ~XL_MACCTRL_DUPLEX;
		if (sc->xl_type == XL_TYPE_905B)
			macctl &= ~XL_MACCTRL_FLOW_CONTROL_ENB;
	}
	CSR_WRITE_1(sc, XL_W3_MAC_CTRL, macctl);
}