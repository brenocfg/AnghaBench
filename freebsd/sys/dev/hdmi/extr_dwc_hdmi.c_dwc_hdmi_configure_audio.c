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
typedef  int uint8_t ;
struct TYPE_2__ {int dot_clock; } ;
struct dwc_hdmi_softc {scalar_t__ sc_has_audio; TYPE_1__ sc_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_AUD_CONF0 ; 
 int HDMI_AUD_CONF0_I2SINEN_CH2 ; 
 int HDMI_AUD_CONF0_I2SINEN_MASK ; 
 int HDMI_AUD_CONF0_INTERFACE_IIS ; 
 int HDMI_AUD_CONF0_INTERFACE_MASK ; 
 int /*<<< orphan*/  HDMI_AUD_CONF1 ; 
 int HDMI_AUD_CONF1_DATAMODE_IIS ; 
 int HDMI_AUD_CONF1_DATAMODE_MASK ; 
 int HDMI_AUD_CONF1_DATWIDTH_16BIT ; 
 int HDMI_AUD_CONF1_DATWIDTH_MASK ; 
 int /*<<< orphan*/  HDMI_AUD_CTS3 ; 
 int HDMI_AUD_CTS3_CTS_MANUAL ; 
 int HDMI_AUD_CTS3_N_SHIFT_MASK ; 
 int /*<<< orphan*/  HDMI_AUD_INPUTCLKFS ; 
 int HDMI_AUD_INPUTCLKFS_64 ; 
 int /*<<< orphan*/  HDMI_AUD_N1 ; 
 int /*<<< orphan*/  HDMI_AUD_N2 ; 
 int /*<<< orphan*/  HDMI_AUD_N3 ; 
 int /*<<< orphan*/  HDMI_FC_AUDICONF0 ; 
 int /*<<< orphan*/  HDMI_FC_AUDICONF1 ; 
 int /*<<< orphan*/  HDMI_FC_AUDICONF2 ; 
 int /*<<< orphan*/  HDMI_FC_AUDICONF3 ; 
 int /*<<< orphan*/  HDMI_FC_AUDSV ; 
 int /*<<< orphan*/  HDMI_MC_CLKDIS ; 
 int HDMI_MC_CLKDIS_AUDCLK_DISABLE ; 
 int RD1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dwc_hdmi_configure_audio(struct dwc_hdmi_softc *sc)
{
	unsigned int n;
	uint8_t val;

	if (sc->sc_has_audio == 0)
		return;

	/* The following values are for 48 kHz */
	switch (sc->sc_mode.dot_clock) {
	case 25170:
		n = 6864;
		break;
	case 27020:
		n = 6144;
		break;
	case 74170:
		n = 11648;
		break;
	case 148350:
		n = 5824;
		break;
	default:
		n = 6144;
		break;
	}

	WR1(sc, HDMI_AUD_N1, (n >> 0) & 0xff);
	WR1(sc, HDMI_AUD_N2, (n >> 8) & 0xff);
	WR1(sc, HDMI_AUD_N3, (n >> 16) & 0xff);

	val = RD1(sc, HDMI_AUD_CTS3);
	val &= ~(HDMI_AUD_CTS3_N_SHIFT_MASK | HDMI_AUD_CTS3_CTS_MANUAL);
	WR1(sc, HDMI_AUD_CTS3, val);

	val = RD1(sc, HDMI_AUD_CONF0);
	val &= ~HDMI_AUD_CONF0_INTERFACE_MASK;
	val |= HDMI_AUD_CONF0_INTERFACE_IIS;
	val &= ~HDMI_AUD_CONF0_I2SINEN_MASK;
	val |= HDMI_AUD_CONF0_I2SINEN_CH2;
	WR1(sc, HDMI_AUD_CONF0, val);

	val = RD1(sc, HDMI_AUD_CONF1);
	val &= ~HDMI_AUD_CONF1_DATAMODE_MASK;
	val |= HDMI_AUD_CONF1_DATAMODE_IIS;
	val &= ~HDMI_AUD_CONF1_DATWIDTH_MASK;
	val |= HDMI_AUD_CONF1_DATWIDTH_16BIT;
	WR1(sc, HDMI_AUD_CONF1, val);

	WR1(sc, HDMI_AUD_INPUTCLKFS, HDMI_AUD_INPUTCLKFS_64);

	WR1(sc, HDMI_FC_AUDICONF0, 1 << 4);	/* CC=1 */
	WR1(sc, HDMI_FC_AUDICONF1, 0);
	WR1(sc, HDMI_FC_AUDICONF2, 0);		/* CA=0 */
	WR1(sc, HDMI_FC_AUDICONF3, 0);
	WR1(sc, HDMI_FC_AUDSV, 0xee);		/* channels valid */

	/* Enable audio clock */
	val = RD1(sc, HDMI_MC_CLKDIS);
	val &= ~HDMI_MC_CLKDIS_AUDCLK_DISABLE;
	WR1(sc, HDMI_MC_CLKDIS, val);
}