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
typedef  int u_int ;
struct videomode {int flags; int hdisplay; int vdisplay; int hsync_end; int hsync_start; int htotal; int vsync_end; int vsync_start; int vtotal; int /*<<< orphan*/  dot_clock; } ;
struct a10fb_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  clk_t ;

/* Variables and functions */
 int BASIC3_HBP (int) ; 
 int BASIC3_HT (int) ; 
 int BASIC4_VBP (int) ; 
 int BASIC4_VT (int) ; 
 int BASIC5_HSPW (int) ; 
 int BASIC5_VSPW (int) ; 
 int BASIC_X (int) ; 
 int BASIC_Y (int) ; 
 int DCLK_EN ; 
 int DIVIDE (int,int) ; 
 int DOT_CLOCK_TO_HZ (int /*<<< orphan*/ ) ; 
 int GCTL_IO_MAP_SEL_TCON1 ; 
 int GINT1_TCON1_LINENO (int) ; 
 int INTERLACE_EN ; 
 int IO_POL_IO2_INV ; 
 int IO_POL_PHSYNC ; 
 int IO_POL_PVSYNC ; 
 int IO_TRI_MASK ; 
 int START_DELAY (int) ; 
 int /*<<< orphan*/  TCON0_DCLK ; 
 int /*<<< orphan*/  TCON1_BASIC0 ; 
 int /*<<< orphan*/  TCON1_BASIC1 ; 
 int /*<<< orphan*/  TCON1_BASIC2 ; 
 int /*<<< orphan*/  TCON1_BASIC3 ; 
 int /*<<< orphan*/  TCON1_BASIC4 ; 
 int /*<<< orphan*/  TCON1_BASIC5 ; 
 int /*<<< orphan*/  TCON1_CTL ; 
 int TCON1_EN ; 
 int /*<<< orphan*/  TCON1_IO_POL ; 
 int /*<<< orphan*/  TCON1_IO_TRI ; 
 int /*<<< orphan*/  TCON1_SRC_CH1 ; 
 int TCON1_SRC_SEL (int /*<<< orphan*/ ) ; 
 int TCON1_START_DELAY (int) ; 
 int /*<<< orphan*/  TCON_GCTL ; 
 int /*<<< orphan*/  TCON_GINT1 ; 
 int /*<<< orphan*/  TCON_WRITE (struct a10fb_softc*,int /*<<< orphan*/ ,int) ; 
 int VBLANK_LEN (int,int,int) ; 
 int VID_INTERLACE ; 
 int VID_PHSYNC ; 
 int VID_PVSYNC ; 
 int VTOTAL (int) ; 
 int a10fb_setup_pll (struct a10fb_softc*,int) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
a10fb_setup_tcon(struct a10fb_softc *sc, const struct videomode *mode)
{
	u_int interlace, hspw, hbp, vspw, vbp, vbl, width, height, start_delay;
	u_int vtotal, framerate, clk;
	clk_t clk_ahb;
	hwreset_t rst;
	uint32_t val;
	int error;

	interlace = !!(mode->flags & VID_INTERLACE);
	width = mode->hdisplay;
	height = mode->vdisplay;
	hspw = mode->hsync_end - mode->hsync_start;
	hbp = mode->htotal - mode->hsync_start;
	vspw = mode->vsync_end - mode->vsync_start;
	vbp = mode->vtotal - mode->vsync_start;
	vbl = VBLANK_LEN(mode->vtotal, mode->vdisplay, interlace);
	start_delay = START_DELAY(vbl);

	/* Leave reset */
	error = hwreset_get_by_ofw_name(sc->dev, 0, "lcd", &rst);
	if (error != 0) {
		device_printf(sc->dev, "cannot find reset 'lcd'\n");
		return (error);
	}
	error = hwreset_deassert(rst);
	if (error != 0) {
		device_printf(sc->dev, "couldn't de-assert reset 'lcd'\n");
		return (error);
	}
	/* Gating AHB clock for LCD */
	error = clk_get_by_ofw_name(sc->dev, 0, "ahb_lcd", &clk_ahb);
	if (error != 0) {
		device_printf(sc->dev, "cannot find clk 'ahb_lcd'\n");
		return (error);
	}
	error = clk_enable(clk_ahb);
	if (error != 0) {
		device_printf(sc->dev, "cannot enable clk 'ahb_lcd'\n");
		return (error);
	}

	/* Disable TCON and TCON1 */
	TCON_WRITE(sc, TCON_GCTL, 0);
	TCON_WRITE(sc, TCON1_CTL, 0);

	/* Enable clocks */
	TCON_WRITE(sc, TCON0_DCLK, DCLK_EN);

	/* Disable IO and data output ports */
	TCON_WRITE(sc, TCON1_IO_TRI, IO_TRI_MASK);

	/* Disable TCON and select TCON1 */
	TCON_WRITE(sc, TCON_GCTL, GCTL_IO_MAP_SEL_TCON1);

	/* Source width and height */
	TCON_WRITE(sc, TCON1_BASIC0, BASIC_X(width) | BASIC_Y(height));
	/* Scaler width and height */
	TCON_WRITE(sc, TCON1_BASIC1, BASIC_X(width) | BASIC_Y(height));
	/* Output width and height */
	TCON_WRITE(sc, TCON1_BASIC2, BASIC_X(width) | BASIC_Y(height));
	/* Horizontal total and back porch */
	TCON_WRITE(sc, TCON1_BASIC3, BASIC3_HT(mode->htotal) | BASIC3_HBP(hbp));
	/* Vertical total and back porch */
	vtotal = VTOTAL(mode->vtotal);
	if (interlace) {
		framerate = DIVIDE(DIVIDE(DOT_CLOCK_TO_HZ(mode->dot_clock),
		    mode->htotal), mode->vtotal);
		clk = mode->htotal * (VTOTAL(mode->vtotal) + 1) * framerate;
		if ((clk / 2) == DOT_CLOCK_TO_HZ(mode->dot_clock))
			vtotal += 1;
	}
	TCON_WRITE(sc, TCON1_BASIC4, BASIC4_VT(vtotal) | BASIC4_VBP(vbp));
	/* Horizontal and vertical sync */
	TCON_WRITE(sc, TCON1_BASIC5, BASIC5_HSPW(hspw) | BASIC5_VSPW(vspw));
	/* Polarity */
	val = IO_POL_IO2_INV;
	if (mode->flags & VID_PHSYNC)
		val |= IO_POL_PHSYNC;
	if (mode->flags & VID_PVSYNC)
		val |= IO_POL_PVSYNC;
	TCON_WRITE(sc, TCON1_IO_POL, val);

	/* Set scan line for TCON1 line trigger */
	TCON_WRITE(sc, TCON_GINT1, GINT1_TCON1_LINENO(start_delay));

	/* Enable TCON1 */
	val = TCON1_EN;
	if (interlace)
		val |= INTERLACE_EN;
	val |= TCON1_START_DELAY(start_delay);
	val |= TCON1_SRC_SEL(TCON1_SRC_CH1);
	TCON_WRITE(sc, TCON1_CTL, val);

	/* Setup PLL */
	return (a10fb_setup_pll(sc, DOT_CLOCK_TO_HZ(mode->dot_clock)));
}