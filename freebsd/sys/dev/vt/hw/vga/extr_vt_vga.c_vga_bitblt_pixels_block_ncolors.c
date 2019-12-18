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
struct vt_device {struct vga_softc* vd_softc; } ;
struct vga_softc {int dummy; } ;
typedef  int /*<<< orphan*/  plans ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_WRITE1 (struct vga_softc*,unsigned int,int) ; 
 int /*<<< orphan*/  REG_WRITE1 (struct vga_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGA_SEQ_ADDRESS ; 
 int /*<<< orphan*/  VGA_SEQ_DATA ; 
 int VGA_SEQ_MAP_MASK ; 
 unsigned int VT_VGA_WIDTH ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_setwmode (struct vt_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vga_bitblt_pixels_block_ncolors(struct vt_device *vd, const uint8_t *masks,
    unsigned int x, unsigned int y, unsigned int height)
{
	unsigned int i, j, plan, color, offset;
	struct vga_softc *sc;
	uint8_t mask, plans[height * 4];

	sc = vd->vd_softc;

	memset(plans, 0, sizeof(plans));

	/*
         * To write a group of pixels using 3 or more colors, we select
         * Write Mode 0 and write one byte to each plan separately.
	 */

	/*
	 * We first compute each byte: each plan contains one bit of the
	 * color code for each of the 8 pixels.
	 *
	 * For example, if the 8 pixels are like this:
	 *     GBBBBBBY
	 * where:
	 *     G (gray)   = 0b0111
	 *     B (black)  = 0b0000
	 *     Y (yellow) = 0b0011
	 *
	 * The corresponding for bytes are:
	 *             GBBBBBBY
	 *     Plan 0: 10000001 = 0x81
	 *     Plan 1: 10000001 = 0x81
	 *     Plan 2: 10000000 = 0x80
	 *     Plan 3: 00000000 = 0x00
	 *             |  |   |
	 *             |  |   +-> 0b0011 (Y)
	 *             |  +-----> 0b0000 (B)
	 *             +--------> 0b0111 (G)
	 */

	for (i = 0; i < height; ++i) {
		for (color = 0; color < 16; ++color) {
			mask = masks[i * 16 + color];
			if (mask == 0x00)
				continue;

			for (j = 0; j < 8; ++j) {
				if (!((mask >> (7 - j)) & 0x1))
					continue;

				/* The pixel "j" uses color "color". */
				for (plan = 0; plan < 4; ++plan)
					plans[i * 4 + plan] |=
					    ((color >> plan) & 0x1) << (7 - j);
			}
		}
	}

	/*
	 * The bytes are ready: we now switch to Write Mode 0 and write
	 * all bytes, one plan at a time.
	 */
	vga_setwmode(vd, 0);

	REG_WRITE1(sc, VGA_SEQ_ADDRESS, VGA_SEQ_MAP_MASK);
	for (plan = 0; plan < 4; ++plan) {
		/* Select plan. */
		REG_WRITE1(sc, VGA_SEQ_DATA, 1 << plan);

		/* Write all bytes for this plan, from Y to Y+height. */
		for (i = 0; i < height; ++i) {
			offset = (VT_VGA_WIDTH * (y + i) + x) / 8;
			MEM_WRITE1(sc, offset, plans[i * 4 + plan]);
		}
	}
}