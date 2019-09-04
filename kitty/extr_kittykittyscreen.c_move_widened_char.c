#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* index_type ;
struct TYPE_14__ {int /*<<< orphan*/ * gpu_cells; int /*<<< orphan*/ * cpu_cells; } ;
struct TYPE_13__ {TYPE_9__* line; int /*<<< orphan*/ * line_attrs; } ;
struct TYPE_10__ {scalar_t__ mDECAWM; } ;
struct TYPE_12__ {void* columns; TYPE_2__* cursor; TYPE_7__* linebuf; TYPE_1__ modes; } ;
struct TYPE_11__ {size_t y; void* x; } ;
typedef  TYPE_3__ Screen ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK_CHAR ; 
 int /*<<< orphan*/  CONTINUED_MASK ; 
 void* MIN (int,void*) ; 
 int /*<<< orphan*/  line_clear_text (TYPE_9__*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  screen_carriage_return (TYPE_3__*) ; 
 int /*<<< orphan*/  screen_linefeed (TYPE_3__*) ; 

__attribute__((used)) static inline void
move_widened_char(Screen *self, CPUCell* cpu_cell, GPUCell *gpu_cell, index_type xpos, index_type ypos) {
    self->cursor->x = xpos; self->cursor->y = ypos;
    CPUCell src_cpu = *cpu_cell, *dest_cpu;
    GPUCell src_gpu = *gpu_cell, *dest_gpu;
    line_clear_text(self->linebuf->line, xpos, 1, BLANK_CHAR);

    if (self->modes.mDECAWM) {  // overflow goes onto next line
        screen_carriage_return(self);
        screen_linefeed(self);
        self->linebuf->line_attrs[self->cursor->y] |= CONTINUED_MASK;
        linebuf_init_line(self->linebuf, self->cursor->y);
        dest_cpu = self->linebuf->line->cpu_cells;
        dest_gpu = self->linebuf->line->gpu_cells;
        self->cursor->x = MIN(2, self->columns);
        linebuf_mark_line_dirty(self->linebuf, self->cursor->y);
    } else {
        dest_cpu = cpu_cell - 1;
        dest_gpu = gpu_cell - 1;
        self->cursor->x = self->columns;
    }
    *dest_cpu = src_cpu;
    *dest_gpu = src_gpu;
}