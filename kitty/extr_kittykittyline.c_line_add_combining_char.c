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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {void** cc_idx; scalar_t__ ch; } ;
struct TYPE_6__ {TYPE_3__* cpu_cells; TYPE_1__* gpu_cells; } ;
struct TYPE_5__ {int attrs; } ;
typedef  TYPE_2__ Line ;
typedef  TYPE_3__ CPUCell ;

/* Variables and functions */
 int WIDTH_MASK ; 
 int arraysz (void**) ; 
 void* mark_for_codepoint (int /*<<< orphan*/ ) ; 

void
line_add_combining_char(Line *self, uint32_t ch, unsigned int x) {
    CPUCell *cell = self->cpu_cells + x;
    if (!cell->ch) {
        if (x > 0 && (self->gpu_cells[x-1].attrs & WIDTH_MASK) == 2 && self->cpu_cells[x-1].ch) cell = self->cpu_cells + x - 1;
        else return; // don't allow adding combining chars to a null cell
    }
    for (unsigned i = 0; i < arraysz(cell->cc_idx); i++) {
        if (!cell->cc_idx[i]) { cell->cc_idx[i] = mark_for_codepoint(ch); return; }
    }
    cell->cc_idx[arraysz(cell->cc_idx) - 1] = mark_for_codepoint(ch);
}