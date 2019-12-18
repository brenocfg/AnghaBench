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
struct videomode {int flags; int hdisplay; int vdisplay; } ;
struct a10fb_softc {int /*<<< orphan*/  paddr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  clk_t ;

/* Variables and functions */
 int ATTCTL1_FBFMT (int /*<<< orphan*/ ) ; 
 int ATTCTL1_FBPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_SET_ROUND_DOWN ; 
 int DEBE_ATTCTL1 ; 
 int DEBE_DISSIZE ; 
 int /*<<< orphan*/  DEBE_FREQ ; 
 int DEBE_LAYCOOR0 ; 
 int DEBE_LAYFB_H4ADD ; 
 int DEBE_LAYFB_L32ADD0 ; 
 int DEBE_LAYLINEWIDTH0 ; 
 int DEBE_LAYSIZE0 ; 
 int DEBE_MODCTL ; 
 int DEBE_READ (struct a10fb_softc*,int) ; 
 int DEBE_REGBUFFCTL ; 
 int DEBE_REG_END ; 
 int DEBE_REG_START ; 
 scalar_t__ DEBE_REG_WIDTH ; 
 int /*<<< orphan*/  DEBE_WRITE (struct a10fb_softc*,int,int) ; 
 int DIS_HEIGHT (int) ; 
 int DIS_WIDTH (int) ; 
 int /*<<< orphan*/  FBFMT_XRGB8888 ; 
 int /*<<< orphan*/  FBPS_32BPP_ARGB ; 
 int FB_BPP ; 
 int LAY0FB_H4ADD (int /*<<< orphan*/ ) ; 
 int LAYFB_L32ADD (int /*<<< orphan*/ ) ; 
 int LAY_HEIGHT (int) ; 
 int LAY_WIDTH (int) ; 
 int LAY_XCOOR (int /*<<< orphan*/ ) ; 
 int LAY_YCOOR (int /*<<< orphan*/ ) ; 
 int MODCTL_EN ; 
 int MODCTL_ITLMOD_EN ; 
 int MODCTL_LAY0_EN ; 
 int MODCTL_OUT_SEL (int /*<<< orphan*/ ) ; 
 int MODCTL_OUT_SEL_MASK ; 
 int MODCTL_START_CTL ; 
 int /*<<< orphan*/  OUT_SEL_LCD ; 
 int REGBUFFCTL_LOAD ; 
 int VID_INTERLACE ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
a10fb_setup_debe(struct a10fb_softc *sc, const struct videomode *mode)
{
	int width, height, interlace, reg;
	clk_t clk_ahb, clk_dram, clk_debe;
	hwreset_t rst;
	uint32_t val;
	int error;

	interlace = !!(mode->flags & VID_INTERLACE);
	width = mode->hdisplay;
	height = mode->vdisplay << interlace;

	/* Leave reset */
	error = hwreset_get_by_ofw_name(sc->dev, 0, "de_be", &rst);
	if (error != 0) {
		device_printf(sc->dev, "cannot find reset 'de_be'\n");
		return (error);
	}
	error = hwreset_deassert(rst);
	if (error != 0) {
		device_printf(sc->dev, "couldn't de-assert reset 'de_be'\n");
		return (error);
	}
	/* Gating AHB clock for BE */
	error = clk_get_by_ofw_name(sc->dev, 0, "ahb_de_be", &clk_ahb);
	if (error != 0) {
		device_printf(sc->dev, "cannot find clk 'ahb_de_be'\n");
		return (error);
	}
	error = clk_enable(clk_ahb);
	if (error != 0) {
		device_printf(sc->dev, "cannot enable clk 'ahb_de_be'\n");
		return (error);
	}
	/* Enable DRAM clock to BE */
	error = clk_get_by_ofw_name(sc->dev, 0, "dram_de_be", &clk_dram);
	if (error != 0) {
		device_printf(sc->dev, "cannot find clk 'dram_de_be'\n");
		return (error);
	}
	error = clk_enable(clk_dram);
	if (error != 0) {
		device_printf(sc->dev, "cannot enable clk 'dram_de_be'\n");
		return (error);
	}
	/* Set BE clock to 300MHz and enable */
	error = clk_get_by_ofw_name(sc->dev, 0, "de_be", &clk_debe);
	if (error != 0) {
		device_printf(sc->dev, "cannot find clk 'de_be'\n");
		return (error);
	}
	error = clk_set_freq(clk_debe, DEBE_FREQ, CLK_SET_ROUND_DOWN);
	if (error != 0) {
		device_printf(sc->dev, "cannot set 'de_be' frequency\n");
		return (error);
	}
	error = clk_enable(clk_debe);
	if (error != 0) {
		device_printf(sc->dev, "cannot enable clk 'de_be'\n");
		return (error);
	}

	/* Initialize all registers to 0 */
	for (reg = DEBE_REG_START; reg < DEBE_REG_END; reg += DEBE_REG_WIDTH)
		DEBE_WRITE(sc, reg, 0);

	/* Enable display backend */
	DEBE_WRITE(sc, DEBE_MODCTL, MODCTL_EN);

	/* Set display size */
	DEBE_WRITE(sc, DEBE_DISSIZE, DIS_HEIGHT(height) | DIS_WIDTH(width));

	/* Set layer 0 size, position, and stride */
	DEBE_WRITE(sc, DEBE_LAYSIZE0, LAY_HEIGHT(height) | LAY_WIDTH(width));
	DEBE_WRITE(sc, DEBE_LAYCOOR0, LAY_XCOOR(0) | LAY_YCOOR(0));
	DEBE_WRITE(sc, DEBE_LAYLINEWIDTH0, width * FB_BPP);

	/* Point layer 0 to FB memory */
	DEBE_WRITE(sc, DEBE_LAYFB_L32ADD0, LAYFB_L32ADD(sc->paddr));
	DEBE_WRITE(sc, DEBE_LAYFB_H4ADD, LAY0FB_H4ADD(sc->paddr));

	/* Set backend format and pixel sequence */
	DEBE_WRITE(sc, DEBE_ATTCTL1, ATTCTL1_FBFMT(FBFMT_XRGB8888) |
	    ATTCTL1_FBPS(FBPS_32BPP_ARGB));

	/* Enable layer 0, output to LCD, setup interlace */
	val = DEBE_READ(sc, DEBE_MODCTL);
	val |= MODCTL_LAY0_EN;
	val &= ~MODCTL_OUT_SEL_MASK;
	val |= MODCTL_OUT_SEL(OUT_SEL_LCD);
	if (interlace)
		val |= MODCTL_ITLMOD_EN;
	else
		val &= ~MODCTL_ITLMOD_EN;
	DEBE_WRITE(sc, DEBE_MODCTL, val);

	/* Commit settings */
	DEBE_WRITE(sc, DEBE_REGBUFFCTL, REGBUFFCTL_LOAD);

	/* Start DEBE */
	val = DEBE_READ(sc, DEBE_MODCTL);
	val |= MODCTL_START_CTL;
	DEBE_WRITE(sc, DEBE_MODCTL, val);

	return (0);
}