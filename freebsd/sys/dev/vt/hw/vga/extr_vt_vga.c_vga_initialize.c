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
typedef  int uint8_t ;
typedef  scalar_t__ u_int ;
struct vt_device {struct vga_softc* vd_softc; } ;
struct vga_softc {int vga_wmode; int vga_curfg; int vga_curbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MEM_WRITE1 (struct vga_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int REG_READ1 (struct vga_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE1 (struct vga_softc*,int /*<<< orphan*/ ,int) ; 
 int VGA_AC_COLOR_PLANE_ENABLE ; 
 int VGA_AC_COLOR_SELECT ; 
 int VGA_AC_HORIZ_PIXEL_PANNING ; 
 int VGA_AC_MC_GA ; 
 int VGA_AC_MODE_CONTROL ; 
 int VGA_AC_OVERSCAN_COLOR ; 
 int VGA_AC_PALETTE (int) ; 
 int VGA_AC_PAL_B ; 
 int VGA_AC_PAL_G ; 
 int VGA_AC_PAL_R ; 
 int VGA_AC_PAL_SB ; 
 int VGA_AC_PAL_SG ; 
 int VGA_AC_PAL_SR ; 
 int /*<<< orphan*/  VGA_AC_WRITE ; 
 int /*<<< orphan*/  VGA_CRTC_ADDRESS ; 
 int VGA_CRTC_CS_COO ; 
 int VGA_CRTC_CURSOR_END ; 
 int VGA_CRTC_CURSOR_LOC_HIGH ; 
 int VGA_CRTC_CURSOR_LOC_LOW ; 
 int VGA_CRTC_CURSOR_START ; 
 int /*<<< orphan*/  VGA_CRTC_DATA ; 
 int VGA_CRTC_MC_HR ; 
 int VGA_CRTC_MODE_CONTROL ; 
 int VGA_CRTC_PRESET_ROW_SCAN ; 
 int VGA_CRTC_START_ADDR_HIGH ; 
 int VGA_CRTC_START_ADDR_LOW ; 
 int VGA_CRTC_UL_UL ; 
 int VGA_CRTC_UNDERLINE_LOC ; 
 int VGA_CRTC_VERT_RETRACE_END ; 
 int VGA_CRTC_VRE_PR ; 
 int /*<<< orphan*/  VGA_GC_ADDRESS ; 
 int /*<<< orphan*/  VGA_GC_DATA ; 
 int VGA_GC_ENABLE_SET_RESET ; 
 int VGA_GC_MODE ; 
 int /*<<< orphan*/  VGA_GEN_INPUT_STAT_1 ; 
 int VGA_GEN_IS1_DE ; 
 int VGA_GEN_IS1_VR ; 
 int /*<<< orphan*/  VGA_GEN_MISC_OUTPUT_R ; 
 int /*<<< orphan*/  VGA_GEN_MISC_OUTPUT_W ; 
 int VGA_GEN_MO_IOA ; 
 int /*<<< orphan*/  VGA_SEQ_ADDRESS ; 
 int /*<<< orphan*/  VGA_SEQ_DATA ; 
 int VGA_SEQ_RESET ; 
 int VGA_SEQ_RST_NAR ; 
 int VGA_SEQ_RST_SR ; 
 scalar_t__ VT_VGA_MEMSIZE ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vga_initialize_graphics (struct vt_device*) ; 

__attribute__((used)) static int
vga_initialize(struct vt_device *vd, int textmode)
{
	struct vga_softc *sc = vd->vd_softc;
	uint8_t x;
	int timeout;

	/* Make sure the VGA adapter is not in monochrome emulation mode. */
	x = REG_READ1(sc, VGA_GEN_MISC_OUTPUT_R);
	REG_WRITE1(sc, VGA_GEN_MISC_OUTPUT_W, x | VGA_GEN_MO_IOA);

	/* Unprotect CRTC registers 0-7. */
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_VERT_RETRACE_END);
	x = REG_READ1(sc, VGA_CRTC_DATA);
	REG_WRITE1(sc, VGA_CRTC_DATA, x & ~VGA_CRTC_VRE_PR);

	/*
	 * Wait for the vertical retrace.
	 * NOTE: this code reads the VGA_GEN_INPUT_STAT_1 register, which has
	 * the side-effect of clearing the internal flip-flip of the attribute
	 * controller's write register. This means that because this code is
	 * here, we know for sure that the first write to the attribute
	 * controller will be a write to the address register. Removing this
	 * code therefore also removes that guarantee and appropriate measures
	 * need to be taken.
	 */
	timeout = 10000;
	do {
		DELAY(10);
		x = REG_READ1(sc, VGA_GEN_INPUT_STAT_1);
		x &= VGA_GEN_IS1_VR | VGA_GEN_IS1_DE;
	} while (x != (VGA_GEN_IS1_VR | VGA_GEN_IS1_DE) && --timeout != 0);
	if (timeout == 0) {
		printf("Timeout initializing vt_vga\n");
		return (ENXIO);
	}

	/* Now, disable the sync. signals. */
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_MODE_CONTROL);
	x = REG_READ1(sc, VGA_CRTC_DATA);
	REG_WRITE1(sc, VGA_CRTC_DATA, x & ~VGA_CRTC_MC_HR);

	/* Asynchronous sequencer reset. */
	REG_WRITE1(sc, VGA_SEQ_ADDRESS, VGA_SEQ_RESET);
	REG_WRITE1(sc, VGA_SEQ_DATA, VGA_SEQ_RST_SR);

	if (!textmode)
		vga_initialize_graphics(vd);

	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_PRESET_ROW_SCAN);
	REG_WRITE1(sc, VGA_CRTC_DATA, 0);
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_CURSOR_START);
	REG_WRITE1(sc, VGA_CRTC_DATA, VGA_CRTC_CS_COO);
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_CURSOR_END);
	REG_WRITE1(sc, VGA_CRTC_DATA, 0);
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_START_ADDR_HIGH);
	REG_WRITE1(sc, VGA_CRTC_DATA, 0);
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_START_ADDR_LOW);
	REG_WRITE1(sc, VGA_CRTC_DATA, 0);
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_CURSOR_LOC_HIGH);
	REG_WRITE1(sc, VGA_CRTC_DATA, 0);
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_CURSOR_LOC_LOW);
	REG_WRITE1(sc, VGA_CRTC_DATA, 0x59);
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_UNDERLINE_LOC);
	REG_WRITE1(sc, VGA_CRTC_DATA, VGA_CRTC_UL_UL);

	if (textmode) {
		/* Set the attribute controller to blink disable. */
		REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_MODE_CONTROL);
		REG_WRITE1(sc, VGA_AC_WRITE, 0);
	} else {
		/* Set the attribute controller in graphics mode. */
		REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_MODE_CONTROL);
		REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_MC_GA);
		REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_HORIZ_PIXEL_PANNING);
		REG_WRITE1(sc, VGA_AC_WRITE, 0);
	}
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(0));
	REG_WRITE1(sc, VGA_AC_WRITE, 0);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(1));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_B);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(2));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_G);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(3));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_G | VGA_AC_PAL_B);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(4));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_R);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(5));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_R | VGA_AC_PAL_B);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(6));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SG | VGA_AC_PAL_R);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(7));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_R | VGA_AC_PAL_G | VGA_AC_PAL_B);

	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(8));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SR | VGA_AC_PAL_SG |
	    VGA_AC_PAL_SB);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(9));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SR | VGA_AC_PAL_SG |
	    VGA_AC_PAL_SB | VGA_AC_PAL_B);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(10));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SR | VGA_AC_PAL_SG |
	    VGA_AC_PAL_SB | VGA_AC_PAL_G);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(11));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SR | VGA_AC_PAL_SG |
	    VGA_AC_PAL_SB | VGA_AC_PAL_G | VGA_AC_PAL_B);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(12));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SR | VGA_AC_PAL_SG |
	    VGA_AC_PAL_SB | VGA_AC_PAL_R);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(13));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SR | VGA_AC_PAL_SG |
	    VGA_AC_PAL_SB | VGA_AC_PAL_R | VGA_AC_PAL_B);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(14));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SR | VGA_AC_PAL_SG |
	    VGA_AC_PAL_SB | VGA_AC_PAL_R | VGA_AC_PAL_G);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PALETTE(15));
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_PAL_SR | VGA_AC_PAL_SG |
	    VGA_AC_PAL_SB | VGA_AC_PAL_R | VGA_AC_PAL_G | VGA_AC_PAL_B);

	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_OVERSCAN_COLOR);
	REG_WRITE1(sc, VGA_AC_WRITE, 0);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_COLOR_PLANE_ENABLE);
	REG_WRITE1(sc, VGA_AC_WRITE, 0x0f);
	REG_WRITE1(sc, VGA_AC_WRITE, VGA_AC_COLOR_SELECT);
	REG_WRITE1(sc, VGA_AC_WRITE, 0);

	if (!textmode) {
		u_int ofs;

		/*
		 * Done.  Clear the frame buffer.  All bit planes are
		 * enabled, so a single-paged loop should clear all
		 * planes.
		 */
		for (ofs = 0; ofs < VT_VGA_MEMSIZE; ofs++) {
			MEM_WRITE1(sc, ofs, 0);
		}
	}

	/* Re-enable the sequencer. */
	REG_WRITE1(sc, VGA_SEQ_ADDRESS, VGA_SEQ_RESET);
	REG_WRITE1(sc, VGA_SEQ_DATA, VGA_SEQ_RST_SR | VGA_SEQ_RST_NAR);
	/* Re-enable the sync signals. */
	REG_WRITE1(sc, VGA_CRTC_ADDRESS, VGA_CRTC_MODE_CONTROL);
	x = REG_READ1(sc, VGA_CRTC_DATA);
	REG_WRITE1(sc, VGA_CRTC_DATA, x | VGA_CRTC_MC_HR);

	if (!textmode) {
		/* Switch to write mode 3, because we'll mainly do bitblt. */
		REG_WRITE1(sc, VGA_GC_ADDRESS, VGA_GC_MODE);
		REG_WRITE1(sc, VGA_GC_DATA, 3);
		sc->vga_wmode = 3;

		/*
		 * In Write Mode 3, Enable Set/Reset is ignored, but we
		 * use Write Mode 0 to write a group of 8 pixels using
		 * 3 or more colors. In this case, we want to disable
		 * Set/Reset: set Enable Set/Reset to 0.
		 */
		REG_WRITE1(sc, VGA_GC_ADDRESS, VGA_GC_ENABLE_SET_RESET);
		REG_WRITE1(sc, VGA_GC_DATA, 0x00);

		/*
		 * Clear the colors we think are loaded into Set/Reset or
		 * the latches.
		 */
		sc->vga_curfg = sc->vga_curbg = 0xff;
	}

	return (0);
}