#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  used_colors_list ;
typedef  unsigned int uint8_t ;
struct TYPE_9__ {unsigned int tp_col; unsigned int tp_row; } ;
struct TYPE_8__ {unsigned int tp_col; unsigned int tp_row; } ;
struct TYPE_13__ {TYPE_2__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_6__ term_rect_t ;
typedef  size_t term_color_t ;
typedef  int /*<<< orphan*/  term_char_t ;
struct TYPE_11__ {unsigned int tp_col; } ;
struct TYPE_10__ {unsigned int tp_col; unsigned int tp_row; } ;
struct TYPE_12__ {TYPE_4__ tr_end; TYPE_3__ tr_begin; } ;
struct vt_buf {int dummy; } ;
struct vt_window {TYPE_5__ vw_draw_area; struct vt_font* vw_font; struct vt_buf vw_buf; } ;
struct vt_mouse_cursor {unsigned int width; unsigned int height; unsigned int const* map; int /*<<< orphan*/ * mask; } ;
struct vt_font {int vf_height; unsigned int vf_width; } ;
struct vt_device {unsigned int vd_mx_drawn; unsigned int vd_my_drawn; size_t vd_mcursor_fg; size_t vd_mcursor_bg; struct vt_mouse_cursor* vd_mcursor; scalar_t__ vd_mshown; } ;
typedef  int /*<<< orphan*/  pattern_ncolors ;
typedef  int /*<<< orphan*/  pattern_2colors ;

/* Variables and functions */
 int /*<<< orphan*/  VTBUF_GET_FIELD (struct vt_buf const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  VTBUF_ISCURSOR (struct vt_buf const*,unsigned int,unsigned int) ; 
 unsigned int VT_VGA_PIXELS_BLOCK ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vga_bitblt_pixels_block_2colors (struct vt_device*,unsigned int*,size_t,size_t,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vga_bitblt_pixels_block_ncolors (struct vt_device*,unsigned int*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vga_copy_bitmap_portion (unsigned int*,unsigned int*,unsigned int const*,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,size_t,size_t,int) ; 
 int /*<<< orphan*/  vt_determine_colors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*) ; 
 scalar_t__ vt_is_cursor_in_area (struct vt_device*,TYPE_6__*) ; 
 unsigned int* vtfont_lookup (struct vt_font const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vga_bitblt_one_text_pixels_block(struct vt_device *vd,
    const struct vt_window *vw, unsigned int x, unsigned int y)
{
	const struct vt_buf *vb;
	const struct vt_font *vf;
	unsigned int i, col, row, src_x, x_count;
	unsigned int used_colors_list[16], used_colors;
	uint8_t pattern_2colors[vw->vw_font->vf_height];
	uint8_t pattern_ncolors[vw->vw_font->vf_height * 16];
	term_char_t c;
	term_color_t fg, bg;
	const uint8_t *src;

	vb = &vw->vw_buf;
	vf = vw->vw_font;

	/*
	 * The current pixels block.
	 *
	 * We fill it with portions of characters, because both "grids"
	 * may not match.
	 *
	 * i is the index in this pixels block.
	 */

	i = x;
	used_colors = 0;
	memset(used_colors_list, 0, sizeof(used_colors_list));
	memset(pattern_2colors, 0, sizeof(pattern_2colors));
	memset(pattern_ncolors, 0, sizeof(pattern_ncolors));

	if (i < vw->vw_draw_area.tr_begin.tp_col) {
		/*
		 * i is in the margin used to center the text area on
		 * the screen.
		 */

		i = vw->vw_draw_area.tr_begin.tp_col;
	}

	while (i < x + VT_VGA_PIXELS_BLOCK &&
	    i < vw->vw_draw_area.tr_end.tp_col) {
		/*
		 * Find which character is drawn on this pixel in the
		 * pixels block.
		 *
		 * While here, record what colors it uses.
		 */

		col = (i - vw->vw_draw_area.tr_begin.tp_col) / vf->vf_width;
		row = (y - vw->vw_draw_area.tr_begin.tp_row) / vf->vf_height;

		c = VTBUF_GET_FIELD(vb, row, col);
		src = vtfont_lookup(vf, c);

		vt_determine_colors(c, VTBUF_ISCURSOR(vb, row, col), &fg, &bg);
		if ((used_colors_list[fg] & 0x1) != 0x1)
			used_colors++;
		if ((used_colors_list[bg] & 0x2) != 0x2)
			used_colors++;
		used_colors_list[fg] |= 0x1;
		used_colors_list[bg] |= 0x2;

		/*
		 * Compute the portion of the character we want to draw,
		 * because the pixels block may start in the middle of a
		 * character.
		 *
		 * The first pixel to draw in the character is
		 *     the current position -
		 *     the start position of the character
		 *
		 * The last pixel to draw is either
		 *     - the last pixel of the character, or
		 *     - the pixel of the character matching the end of
		 *       the pixels block
		 * whichever comes first. This position is then
		 * changed to be relative to the start position of the
		 * character.
		 */

		src_x = i -
		    (col * vf->vf_width + vw->vw_draw_area.tr_begin.tp_col);
		x_count = min(min(
		    (col + 1) * vf->vf_width +
		    vw->vw_draw_area.tr_begin.tp_col,
		    x + VT_VGA_PIXELS_BLOCK),
		    vw->vw_draw_area.tr_end.tp_col);
		x_count -= col * vf->vf_width +
		    vw->vw_draw_area.tr_begin.tp_col;
		x_count -= src_x;

		/* Copy a portion of the character. */
		vga_copy_bitmap_portion(pattern_2colors, pattern_ncolors,
		    src, NULL, vf->vf_width,
		    src_x, i % VT_VGA_PIXELS_BLOCK, x_count,
		    0, 0, vf->vf_height, fg, bg, 0);

		/* We move to the next portion. */
		i += x_count;
	}

#ifndef SC_NO_CUTPASTE
	/*
	 * Copy the mouse pointer bitmap if it's over the current pixels
	 * block.
	 *
	 * We use the saved cursor position (saved in vt_flush()), because
	 * the current position could be different than the one used
	 * to mark the area dirty.
	 */
	term_rect_t drawn_area;

	drawn_area.tr_begin.tp_col = x;
	drawn_area.tr_begin.tp_row = y;
	drawn_area.tr_end.tp_col = x + VT_VGA_PIXELS_BLOCK;
	drawn_area.tr_end.tp_row = y + vf->vf_height;
	if (vd->vd_mshown && vt_is_cursor_in_area(vd, &drawn_area)) {
		struct vt_mouse_cursor *cursor;
		unsigned int mx, my;
		unsigned int dst_x, src_y, dst_y, y_count;

		cursor = vd->vd_mcursor;
		mx = vd->vd_mx_drawn + vw->vw_draw_area.tr_begin.tp_col;
		my = vd->vd_my_drawn + vw->vw_draw_area.tr_begin.tp_row;

		/* Compute the portion of the cursor we want to copy. */
		src_x = x > mx ? x - mx : 0;
		dst_x = mx > x ? mx - x : 0;
		x_count = min(min(min(
		    cursor->width - src_x,
		    x + VT_VGA_PIXELS_BLOCK - mx),
		    vw->vw_draw_area.tr_end.tp_col - mx),
		    VT_VGA_PIXELS_BLOCK);

		/*
		 * The cursor isn't aligned on the Y-axis with
		 * characters, so we need to compute the vertical
		 * start/count.
		 */
		src_y = y > my ? y - my : 0;
		dst_y = my > y ? my - y : 0;
		y_count = min(
		    min(cursor->height - src_y, y + vf->vf_height - my),
		    vf->vf_height);

		/* Copy the cursor portion. */
		vga_copy_bitmap_portion(pattern_2colors, pattern_ncolors,
		    cursor->map, cursor->mask, cursor->width,
		    src_x, dst_x, x_count, src_y, dst_y, y_count,
		    vd->vd_mcursor_fg, vd->vd_mcursor_bg, 1);

		if ((used_colors_list[vd->vd_mcursor_fg] & 0x1) != 0x1)
			used_colors++;
		if ((used_colors_list[vd->vd_mcursor_bg] & 0x2) != 0x2)
			used_colors++;
	}
#endif

	/*
	 * The pixels block is completed, we can now draw it on the
	 * screen.
	 */
	if (used_colors == 2)
		vga_bitblt_pixels_block_2colors(vd, pattern_2colors, fg, bg,
		    x, y, vf->vf_height);
	else
		vga_bitblt_pixels_block_ncolors(vd, pattern_ncolors,
		    x, y, vf->vf_height);
}