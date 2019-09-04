#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
typedef  int char_type ;
struct TYPE_10__ {int attrs; scalar_t__ fg; scalar_t__ bg; scalar_t__ decoration_fg; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {TYPE_1__* cpu_cells; TYPE_3__* gpu_cells; } ;
struct TYPE_8__ {int ch; scalar_t__* cc_idx; } ;
typedef  int Py_UCS4 ;
typedef  TYPE_2__ Line ;
typedef  TYPE_3__ GPUCell ;

/* Variables and functions */
 int ATTRS_MASK_WITHOUT_WIDTH ; 
 int WIDTH_MASK ; 
 unsigned int arraysz (scalar_t__*) ; 
 char* cell_as_sgr (TYPE_3__*,TYPE_3__*) ; 
 int codepoint_for_mark (scalar_t__) ; 
 int /*<<< orphan*/  write_sgr (char const*,int*,scalar_t__,scalar_t__*) ; 
 scalar_t__ xlimit_for_line (TYPE_2__*) ; 

index_type
line_as_ansi(Line *self, Py_UCS4 *buf, index_type buflen, bool *truncated) {
#define WRITE_SGR(val) { if (!write_sgr(val, buf, buflen, &i)) { *truncated = true; return i; } }
#define WRITE_CH(val) if (i > buflen - 1) { *truncated = true; return i; } buf[i++] = val;

    index_type limit = xlimit_for_line(self), i=0;
    *truncated = false;
    if (limit == 0) return 0;
    char_type previous_width = 0;

    GPUCell blank_cell = { 0 };
    GPUCell *cell, *prev_cell = &blank_cell;

    for (index_type pos=0; pos < limit; pos++) {
        char_type ch = self->cpu_cells[pos].ch;
        if (ch == 0) {
            if (previous_width == 2) { previous_width = 0; continue; }
            ch = ' ';
        }

        cell = &self->gpu_cells[pos];

#define CMP_ATTRS (cell->attrs & ATTRS_MASK_WITHOUT_WIDTH) != (prev_cell->attrs & ATTRS_MASK_WITHOUT_WIDTH)
#define CMP(x) cell->x != prev_cell->x
        if (CMP_ATTRS || CMP(fg) || CMP(bg) || CMP(decoration_fg)) {
            const char *sgr = cell_as_sgr(cell, prev_cell);
            if (*sgr) WRITE_SGR(sgr);
        }
        prev_cell = cell;
        WRITE_CH(ch);
        for(unsigned c = 0; c < arraysz(self->cpu_cells[pos].cc_idx) && self->cpu_cells[pos].cc_idx[c]; c++) {
            WRITE_CH(codepoint_for_mark(self->cpu_cells[pos].cc_idx[c]));
        }
        previous_width = cell->attrs & WIDTH_MASK;
    }
    return i;
#undef CMP_ATTRS
#undef CMP
#undef WRITE_SGR
#undef WRITE_CH
}