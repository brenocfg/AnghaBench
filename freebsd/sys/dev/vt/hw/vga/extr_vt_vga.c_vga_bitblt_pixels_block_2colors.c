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
typedef  int /*<<< orphan*/  term_color_t ;
struct vt_device {struct vga_softc* vd_softc; } ;
struct vga_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_WRITE1 (struct vga_softc*,unsigned int,int /*<<< orphan*/  const) ; 
 unsigned int VT_VGA_WIDTH ; 
 int /*<<< orphan*/  vga_setbg (struct vt_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_setfg (struct vt_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vga_bitblt_pixels_block_2colors(struct vt_device *vd, const uint8_t *masks,
    term_color_t fg, term_color_t bg,
    unsigned int x, unsigned int y, unsigned int height)
{
	unsigned int i, offset;
	struct vga_softc *sc;

	/*
	 * The great advantage of Write Mode 3 is that we just need
	 * to load the foreground in the Set/Reset register, load the
	 * background color in the latches register (this is done
	 * through a write in offscreen memory followed by a read of
	 * that data), then write the pattern to video memory. This
	 * pattern indicates if the pixel should use the foreground
	 * color (bit set) or the background color (bit cleared).
	 */

	vga_setbg(vd, bg);
	vga_setfg(vd, fg);

	sc = vd->vd_softc;
	offset = (VT_VGA_WIDTH * y + x) / 8;

	for (i = 0; i < height; ++i, offset += VT_VGA_WIDTH / 8) {
		MEM_WRITE1(sc, offset, masks[i]);
	}
}