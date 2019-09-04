#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ index_type ;
struct TYPE_11__ {int mDECAWM; } ;
struct TYPE_9__ {int is_active; scalar_t__ xnum; scalar_t__ xstart; int /*<<< orphan*/  ynum; int /*<<< orphan*/  cpu_cells; int /*<<< orphan*/  gpu_cells; } ;
struct TYPE_12__ {TYPE_3__ modes; TYPE_2__* cursor; TYPE_1__ overlay_line; int /*<<< orphan*/  columns; } ;
struct TYPE_10__ {int reverse; scalar_t__ x; int /*<<< orphan*/  y; } ;
typedef  TYPE_4__ Screen ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
#define  UTF8_ACCEPT 129 
#define  UTF8_REJECT 128 
 int /*<<< orphan*/  deactivate_overlay_line (TYPE_4__*) ; 
 int decode_utf8 (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_save_cells (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * range_line_ (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_draw (TYPE_4__*,int) ; 

void
screen_draw_overlay_text(Screen *self, const char *utf8_text) {
    if (self->overlay_line.is_active) deactivate_overlay_line(self);
    if (!utf8_text || !utf8_text[0]) return;
    Line *line = range_line_(self, self->cursor->y);
    if (!line) return;
    line_save_cells(line, 0, self->columns, self->overlay_line.gpu_cells, self->overlay_line.cpu_cells);
    self->overlay_line.is_active = true;
    self->overlay_line.ynum = self->cursor->y;
    self->overlay_line.xstart = self->cursor->x;
    self->overlay_line.xnum = 0;
    uint32_t codepoint = 0, state = UTF8_ACCEPT;
    bool orig_line_wrap_mode = self->modes.mDECAWM;
    self->modes.mDECAWM = false;
    self->cursor->reverse ^= true;
    index_type before;
    while (*utf8_text) {
        switch(decode_utf8(&state, &codepoint, *(utf8_text++))) {
            case UTF8_ACCEPT:
                before = self->cursor->x;
                screen_draw(self, codepoint);
                self->overlay_line.xnum += self->cursor->x - before;
                break;
            case UTF8_REJECT:
                break;
        }
    }
    self->cursor->reverse ^= true;
    self->modes.mDECAWM = orig_line_wrap_mode;
}