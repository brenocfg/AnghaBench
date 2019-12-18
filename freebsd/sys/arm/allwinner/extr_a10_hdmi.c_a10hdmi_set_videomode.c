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
struct videomode {int flags; int hsync_start; int hdisplay; int hsync_end; int htotal; int vsync_start; int vdisplay; int vsync_end; int vtotal; } ;
struct a10hdmi_softc {scalar_t__ has_hdmi; scalar_t__ has_audio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_INT_STATUS ; 
 int /*<<< orphan*/  HDMI_PADCTRL1 ; 
 int /*<<< orphan*/  HDMI_PKTCTRL0 ; 
 int /*<<< orphan*/  HDMI_PKTCTRL1 ; 
 int /*<<< orphan*/  HDMI_PLLCTRL0 ; 
 int HDMI_READ (struct a10hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_VID_CTRL ; 
 int /*<<< orphan*/  HDMI_VID_TIMING0 ; 
 int /*<<< orphan*/  HDMI_VID_TIMING1 ; 
 int /*<<< orphan*/  HDMI_VID_TIMING2 ; 
 int /*<<< orphan*/  HDMI_VID_TIMING3 ; 
 int /*<<< orphan*/  HDMI_VID_TIMING4 ; 
 int /*<<< orphan*/  HDMI_WRITE (struct a10hdmi_softc*,int /*<<< orphan*/ ,int) ; 
 int PADCTRL1_REG_CKSS ; 
 int PADCTRL1_REG_CKSS_1X ; 
 int PADCTRL1_REG_CKSS_2X ; 
 int PKTCTRL_PACKET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_AI ; 
 int /*<<< orphan*/  PKT_AVI ; 
 int /*<<< orphan*/  PKT_END ; 
 int /*<<< orphan*/  PKT_GC ; 
 int PLLCTRL0_BWS ; 
 int PLLCTRL0_CP_S ; 
 int PLLCTRL0_CS ; 
 int PLLCTRL0_HV_IS_33 ; 
 int PLLCTRL0_LDO1_EN ; 
 int PLLCTRL0_LDO2_EN ; 
 int PLLCTRL0_PLL_EN ; 
 int PLLCTRL0_PREDIV (int) ; 
 int PLLCTRL0_S ; 
 int PLLCTRL0_SDIV2 ; 
 int PLLCTRL0_VCO_GAIN ; 
 int PLLCTRL0_VCO_S ; 
 int TX_CLOCK_NORMAL ; 
 int VID_ACT_H (int) ; 
 int VID_ACT_V (int) ; 
 int VID_CTRL_HDMI_MODE ; 
 int VID_CTRL_INTERLACE ; 
 int VID_CTRL_REPEATER_2X ; 
 int VID_DBLSCAN ; 
 int VID_HBP (int) ; 
 int VID_HFP (int) ; 
 int VID_HSPW (int) ; 
 int VID_HSYNC_ACTSEL ; 
 int VID_INTERLACE ; 
 int VID_PHSYNC ; 
 int VID_PVSYNC ; 
 int VID_VBP (int) ; 
 int VID_VFP (int) ; 
 int VID_VSPW (int) ; 
 int VID_VSYNC_ACTSEL ; 
 int a10hdmi_get_tcon_config (struct a10hdmi_softc*,int*,int*) ; 
 int /*<<< orphan*/  a10hdmi_set_audiomode (int /*<<< orphan*/ ,struct videomode const*) ; 
 scalar_t__ bootverbose ; 
 struct a10hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
a10hdmi_set_videomode(device_t dev, const struct videomode *mode)
{
	struct a10hdmi_softc *sc;
	int error, clk_div, clk_dbl;
	int dblscan, hfp, hspw, hbp, vfp, vspw, vbp;
	uint32_t val;

	sc = device_get_softc(dev);
	dblscan = !!(mode->flags & VID_DBLSCAN);
	hfp = mode->hsync_start - mode->hdisplay;
	hspw = mode->hsync_end - mode->hsync_start;
	hbp = mode->htotal - mode->hsync_start;
	vfp = mode->vsync_start - mode->vdisplay;
	vspw = mode->vsync_end - mode->vsync_start;
	vbp = mode->vtotal - mode->vsync_start;

	error = a10hdmi_get_tcon_config(sc, &clk_div, &clk_dbl);
	if (error != 0) {
		device_printf(dev, "couldn't get tcon config: %d\n", error);
		return (error);
	}

	/* Clear interrupt status */
	HDMI_WRITE(sc, HDMI_INT_STATUS, HDMI_READ(sc, HDMI_INT_STATUS));

	/* Clock setup */
	val = HDMI_READ(sc, HDMI_PADCTRL1);
	val &= ~PADCTRL1_REG_CKSS;
	val |= (clk_dbl ? PADCTRL1_REG_CKSS_2X : PADCTRL1_REG_CKSS_1X);
	HDMI_WRITE(sc, HDMI_PADCTRL1, val);
	HDMI_WRITE(sc, HDMI_PLLCTRL0, PLLCTRL0_PLL_EN | PLLCTRL0_BWS |
	    PLLCTRL0_HV_IS_33 | PLLCTRL0_LDO1_EN | PLLCTRL0_LDO2_EN |
	    PLLCTRL0_SDIV2 | PLLCTRL0_VCO_GAIN | PLLCTRL0_S |
	    PLLCTRL0_CP_S | PLLCTRL0_CS | PLLCTRL0_PREDIV(clk_div) |
	    PLLCTRL0_VCO_S);

	/* Setup display settings */
	if (bootverbose)
		device_printf(dev, "HDMI: %s, Audio: %s\n",
		    sc->has_hdmi ? "yes" : "no", sc->has_audio ? "yes" : "no");
	val = 0;
	if (sc->has_hdmi)
		val |= VID_CTRL_HDMI_MODE;
	if (mode->flags & VID_INTERLACE)
		val |= VID_CTRL_INTERLACE;
	if (mode->flags & VID_DBLSCAN)
		val |= VID_CTRL_REPEATER_2X;
	HDMI_WRITE(sc, HDMI_VID_CTRL, val);

	/* Setup display timings */
	HDMI_WRITE(sc, HDMI_VID_TIMING0,
	    VID_ACT_V(mode->vdisplay) | VID_ACT_H(mode->hdisplay << dblscan));
	HDMI_WRITE(sc, HDMI_VID_TIMING1,
	    VID_VBP(vbp) | VID_HBP(hbp << dblscan));
	HDMI_WRITE(sc, HDMI_VID_TIMING2,
	    VID_VFP(vfp) | VID_HFP(hfp << dblscan));
	HDMI_WRITE(sc, HDMI_VID_TIMING3,
	    VID_VSPW(vspw) | VID_HSPW(hspw << dblscan));
	val = TX_CLOCK_NORMAL;
	if (mode->flags & VID_PVSYNC)
		val |= VID_VSYNC_ACTSEL;
	if (mode->flags & VID_PHSYNC)
		val |= VID_HSYNC_ACTSEL;
	HDMI_WRITE(sc, HDMI_VID_TIMING4, val);

	/* This is an ordered list of infoframe packets that the HDMI
	 * transmitter will send. Transmit packets in the following order:
	 *  1. General control packet
	 *  2. AVI infoframe
	 *  3. Audio infoframe
	 * There are 2 registers with 4 slots each. The list is terminated
	 * with the special PKT_END marker.
	 */
	HDMI_WRITE(sc, HDMI_PKTCTRL0,
	    PKTCTRL_PACKET(0, PKT_GC) | PKTCTRL_PACKET(1, PKT_AVI) |
	    PKTCTRL_PACKET(2, PKT_AI) | PKTCTRL_PACKET(3, PKT_END));
	HDMI_WRITE(sc, HDMI_PKTCTRL1, 0);

	/* Setup audio */
	a10hdmi_set_audiomode(dev, mode);

	return (0);
}