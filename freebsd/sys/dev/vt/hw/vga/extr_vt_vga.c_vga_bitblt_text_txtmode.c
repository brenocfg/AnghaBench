#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {unsigned int tp_row; unsigned int tp_col; } ;
struct TYPE_5__ {unsigned int tp_row; unsigned int tp_col; } ;
struct TYPE_7__ {TYPE_2__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_3__ term_rect_t ;
typedef  size_t term_color_t ;
typedef  scalar_t__ term_char_t ;
struct vt_buf {int dummy; } ;
struct vt_window {struct vt_buf vw_buf; } ;
struct vt_device {scalar_t__* vd_drawn; size_t* vd_drawnfg; size_t* vd_drawnbg; struct vga_softc* vd_softc; } ;
struct vga_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_WRITE2 (struct vga_softc*,scalar_t__,int) ; 
 unsigned int PIXEL_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCHAR_CHARACTER (scalar_t__) ; 
 scalar_t__ VTBUF_GET_FIELD (struct vt_buf const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  VTBUF_ISCURSOR (struct vt_buf const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  VT_FB_MAX_WIDTH ; 
 int* cons_to_vga_colors ; 
 int vga_get_cp437 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_determine_colors (scalar_t__,int /*<<< orphan*/ ,size_t*,size_t*) ; 

__attribute__((used)) static void
vga_bitblt_text_txtmode(struct vt_device *vd, const struct vt_window *vw,
    const term_rect_t *area)
{
	struct vga_softc *sc;
	const struct vt_buf *vb;
	unsigned int col, row;
	term_char_t c;
	term_color_t fg, bg;
	uint8_t ch, attr;
	size_t z;

	sc = vd->vd_softc;
	vb = &vw->vw_buf;

	for (row = area->tr_begin.tp_row; row < area->tr_end.tp_row; ++row) {
		for (col = area->tr_begin.tp_col;
		    col < area->tr_end.tp_col;
		    ++col) {
			/*
			 * Get next character and its associated fg/bg
			 * colors.
			 */
			c = VTBUF_GET_FIELD(vb, row, col);
			vt_determine_colors(c, VTBUF_ISCURSOR(vb, row, col),
			    &fg, &bg);

			z = row * PIXEL_WIDTH(VT_FB_MAX_WIDTH) + col;
			if (vd->vd_drawn && (vd->vd_drawn[z] == c) &&
			    vd->vd_drawnfg && (vd->vd_drawnfg[z] == fg) &&
			    vd->vd_drawnbg && (vd->vd_drawnbg[z] == bg))
				continue;

			/*
			 * Convert character to CP437, which is the
			 * character set used by the VGA hardware by
			 * default.
			 */
			ch = vga_get_cp437(TCHAR_CHARACTER(c));

			/* Convert colors to VGA attributes. */
			attr =
			    cons_to_vga_colors[bg] << 4 |
			    cons_to_vga_colors[fg];

			MEM_WRITE2(sc, (row * 80 + col) * 2 + 0,
			    ch + ((uint16_t)(attr) << 8));

			if (vd->vd_drawn)
				vd->vd_drawn[z] = c;
			if (vd->vd_drawnfg)
				vd->vd_drawnfg[z] = fg;
			if (vd->vd_drawnbg)
				vd->vd_drawnbg[z] = bg;
		}
	}
}