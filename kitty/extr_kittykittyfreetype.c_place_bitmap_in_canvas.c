#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  pixel ;
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {scalar_t__ start_x; size_t rows; size_t width; scalar_t__ pixel_mode; int /*<<< orphan*/  stride; int /*<<< orphan*/  buf; scalar_t__ bitmap_top; scalar_t__ bitmap_left; } ;
struct TYPE_8__ {scalar_t__ left; size_t bottom; size_t right; scalar_t__ top; } ;
typedef  TYPE_1__ Region ;
typedef  TYPE_2__ ProcessedBitmap ;

/* Variables and functions */
 scalar_t__ FT_PIXEL_MODE_BGRA ; 
 int /*<<< orphan*/  copy_color_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  render_alpha_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void
place_bitmap_in_canvas(pixel *cell, ProcessedBitmap *bm, size_t cell_width, size_t cell_height, float x_offset, float y_offset, size_t baseline) {
    // We want the glyph to be positioned inside the cell based on the bearingX
    // and bearingY values, making sure that it does not overflow the cell.

    Region src = { .left = bm->start_x, .bottom = bm->rows, .right = bm->width + bm->start_x }, dest = { .bottom = cell_height, .right = cell_width };

    // Calculate column bounds
    int32_t xoff = (ssize_t)(x_offset + bm->bitmap_left);
    uint32_t extra;
    if (xoff < 0) src.left += -xoff;
    else dest.left = xoff;
    // Move the dest start column back if the width overflows because of it
    if (dest.left > 0 && dest.left + bm->width > cell_width) {
        extra = dest.left + bm->width - cell_width;
        dest.left = extra > dest.left ? 0 : dest.left - extra;
    }

    // Calculate row bounds
    int32_t yoff = (ssize_t)(y_offset + bm->bitmap_top);
    if ((yoff > 0 && (size_t)yoff > baseline)) {
        dest.top = 0;
    } else {
        dest.top = baseline - yoff;
    }

    /* printf("x_offset: %d bearing_x: %f y_offset: %d bearing_y: %f src_start_row: %u src_start_column: %u dest_start_row: %u dest_start_column: %u bm_width: %lu bitmap_rows: %lu\n", xoff, bearing_x, yoff, bearing_y, src.top, src.left, dest.top, dest.left, bm->width, bm->rows); */

    if (bm->pixel_mode == FT_PIXEL_MODE_BGRA) {
        copy_color_bitmap(bm->buf, cell, &src, &dest, bm->stride, cell_width);
    } else render_alpha_mask(bm->buf, cell, &src, &dest, bm->stride, cell_width);
}