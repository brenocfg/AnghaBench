#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_12__ {TYPE_2__* line; } ;
struct TYPE_11__ {int top; int left; int bottom; int right; } ;
struct TYPE_8__ {scalar_t__ mDECSACE; scalar_t__ mDECOM; } ;
struct TYPE_10__ {int lines; int columns; int /*<<< orphan*/  cursor; TYPE_7__* linebuf; TYPE_1__ modes; scalar_t__ margin_top; } ;
struct TYPE_9__ {scalar_t__ gpu_cells; } ;
typedef  TYPE_3__ Screen ;
typedef  TYPE_4__ Region ;

/* Variables and functions */
 scalar_t__ MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  apply_sgr_to_cells (scalar_t__,scalar_t__,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  cursor_from_sgr (int /*<<< orphan*/ ,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_7__*,scalar_t__) ; 

void
select_graphic_rendition(Screen *self, unsigned int *params, unsigned int count, Region *region_) {
    if (region_) {
        Region region = *region_;
        if (!region.top) region.top = 1;
        if (!region.left) region.left = 1;
        if (!region.bottom) region.bottom = self->lines;
        if (!region.right) region.right = self->columns;
        if (self->modes.mDECOM) {
            region.top += self->margin_top; region.bottom += self->margin_top;
        }
        region.left -= 1; region.top -= 1; region.right -= 1; region.bottom -= 1;  // switch to zero based indexing
        if (self->modes.mDECSACE) {
            index_type x = MIN(region.left, self->columns - 1);
            index_type num = region.right >= x ? region.right - x + 1 : 0;
            num = MIN(num, self->columns - x);
            for (index_type y = region.top; y < MIN(region.bottom + 1, self->lines); y++) {
                linebuf_init_line(self->linebuf, y);
                apply_sgr_to_cells(self->linebuf->line->gpu_cells + x, num, params, count);
            }
        } else {
            index_type x, num;
            for (index_type y = region.top; y < MIN(region.bottom + 1, self->lines); y++) {
                if (y == region.top) { x = MIN(region.left, self->columns - 1); num = self->columns - x; }
                else if (y == region.bottom) { x = 0; num = MIN(region.right + 1, self->columns); }
                else { x = 0; num = self->columns; }
                linebuf_init_line(self->linebuf, y);
                apply_sgr_to_cells(self->linebuf->line->gpu_cells + x, num, params, count);
            }
        }
    } else cursor_from_sgr(self->cursor, params, count);
}