#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int index_type ;
typedef  int char_type ;
struct TYPE_18__ {TYPE_2__* gpu_cells; TYPE_3__* cpu_cells; } ;
struct TYPE_17__ {TYPE_9__* line; } ;
struct TYPE_16__ {scalar_t__* cc_idx; int /*<<< orphan*/  ch; } ;
struct TYPE_15__ {int attrs; } ;
struct TYPE_14__ {int columns; int is_dirty; TYPE_10__* cursor; TYPE_7__* linebuf; int /*<<< orphan*/  selection; } ;
struct TYPE_13__ {scalar_t__ x; int y; } ;
typedef  TYPE_1__ Screen ;
typedef  TYPE_2__ GPUCell ;
typedef  TYPE_3__ CPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SELECTION ; 
 scalar_t__ VS16 ; 
 int WIDTH_MASK ; 
 scalar_t__ is_emoji_presentation_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_add_combining_char (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  line_set_char (TYPE_9__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,int) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_7__*,int) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (TYPE_7__*,int) ; 
 int /*<<< orphan*/  move_widened_char (TYPE_1__*,TYPE_3__*,TYPE_2__*,int,int) ; 
 scalar_t__ selection_has_screen_line (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
draw_combining_char(Screen *self, char_type ch) {
    bool has_prev_char = false;
    index_type xpos = 0, ypos = 0;
    if (self->cursor->x > 0) {
        ypos = self->cursor->y;
        linebuf_init_line(self->linebuf, ypos);
        xpos = self->cursor->x - 1;
        has_prev_char = true;
    } else if (self->cursor->y > 0) {
        ypos = self->cursor->y - 1;
        linebuf_init_line(self->linebuf, ypos);
        xpos = self->columns - 1;
        has_prev_char = true;
    }
    if (has_prev_char) {
        line_add_combining_char(self->linebuf->line, ch, xpos);
        self->is_dirty = true;
        if (selection_has_screen_line(&self->selection, ypos)) self->selection = EMPTY_SELECTION;
        linebuf_mark_line_dirty(self->linebuf, ypos);
        if (ch == 0xfe0f) {  // emoji presentation variation marker makes default text presentation emoji (narrow emoji) into wide emoji
            CPUCell *cpu_cell = self->linebuf->line->cpu_cells + xpos;
            GPUCell *gpu_cell = self->linebuf->line->gpu_cells + xpos;
            if ((gpu_cell->attrs & WIDTH_MASK) != 2 && cpu_cell->cc_idx[0] == VS16 && is_emoji_presentation_base(cpu_cell->ch)) {
                if (self->cursor->x <= self->columns - 1) line_set_char(self->linebuf->line, self->cursor->x, 0, 0, self->cursor, true);
                gpu_cell->attrs = (gpu_cell->attrs & !WIDTH_MASK) | 2;
                if (xpos == self->columns - 1) move_widened_char(self, cpu_cell, gpu_cell, xpos, ypos);
                else self->cursor->x++;
            }
        }
    }
}