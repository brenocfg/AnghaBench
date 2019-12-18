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
struct TYPE_9__ {unsigned int tp_col; unsigned int tp_row; } ;
struct TYPE_8__ {unsigned int tp_col; unsigned int tp_row; } ;
struct TYPE_13__ {TYPE_2__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_6__ term_rect_t ;
struct TYPE_11__ {int /*<<< orphan*/  tp_row; int /*<<< orphan*/  tp_col; } ;
struct TYPE_10__ {unsigned int tp_col; unsigned int tp_row; } ;
struct TYPE_12__ {TYPE_4__ tr_end; TYPE_3__ tr_begin; } ;
struct vt_window {TYPE_5__ vw_draw_area; struct vt_font* vw_font; } ;
struct vt_font {unsigned int vf_width; unsigned int vf_height; } ;
struct vt_device {int dummy; } ;

/* Variables and functions */
 unsigned int VT_VGA_PIXELS_BLOCK ; 
 scalar_t__ howmany (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_bitblt_one_text_pixels_block (struct vt_device*,struct vt_window const*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
vga_bitblt_text_gfxmode(struct vt_device *vd, const struct vt_window *vw,
    const term_rect_t *area)
{
	const struct vt_font *vf;
	unsigned int col, row;
	unsigned int x1, y1, x2, y2, x, y;

	vf = vw->vw_font;

	/*
	 * Compute the top-left pixel position aligned with the video
	 * adapter pixels block size.
	 *
	 * This is calculated from the top-left column of te dirty area:
	 *
	 *     1. Compute the top-left pixel of the character:
	 *        col * font width + x offset
	 *
	 *        NOTE: x offset is used to center the text area on the
	 *        screen. It's expressed in pixels, not in characters
	 *        col/row!
	 *
	 *     2. Find the pixel further on the left marking the start of
	 *        an aligned pixels block (eg. chunk of 8 pixels):
	 *        character's x / blocksize * blocksize
	 *
	 *        The division, being made on integers, achieves the
	 *        alignment.
	 *
	 * For the Y-axis, we need to compute the character's y
	 * coordinate, but we don't need to align it.
	 */

	col = area->tr_begin.tp_col;
	row = area->tr_begin.tp_row;
	x1 = (int)((col * vf->vf_width + vw->vw_draw_area.tr_begin.tp_col)
	     / VT_VGA_PIXELS_BLOCK)
	    * VT_VGA_PIXELS_BLOCK;
	y1 = row * vf->vf_height + vw->vw_draw_area.tr_begin.tp_row;

	/*
	 * Compute the bottom right pixel position, again, aligned with
	 * the pixels block size.
	 *
	 * The same rules apply, we just add 1 to base the computation
	 * on the "right border" of the dirty area.
	 */

	col = area->tr_end.tp_col;
	row = area->tr_end.tp_row;
	x2 = (int)howmany(col * vf->vf_width + vw->vw_draw_area.tr_begin.tp_col,
	    VT_VGA_PIXELS_BLOCK)
	    * VT_VGA_PIXELS_BLOCK;
	y2 = row * vf->vf_height + vw->vw_draw_area.tr_begin.tp_row;

	/* Clip the area to the screen size. */
	x2 = min(x2, vw->vw_draw_area.tr_end.tp_col);
	y2 = min(y2, vw->vw_draw_area.tr_end.tp_row);

	/*
	 * Now, we take care of N pixels line at a time (the first for
	 * loop, N = font height), and for these lines, draw one pixels
	 * block at a time (the second for loop), not a character at a
	 * time.
	 *
	 * Therefore, on the X-axis, characters my be drawn partially if
	 * they are not aligned on 8-pixels boundary.
	 *
	 * However, the operation is repeated for the full height of the
	 * font before moving to the next character, because it allows
	 * to keep the color settings and write mode, before perhaps
	 * changing them with the next one.
	 */

	for (y = y1; y < y2; y += vf->vf_height) {
		for (x = x1; x < x2; x += VT_VGA_PIXELS_BLOCK) {
			vga_bitblt_one_text_pixels_block(vd, vw, x, y);
		}
	}
}