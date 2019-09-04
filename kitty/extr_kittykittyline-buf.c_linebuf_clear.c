#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line_attrs_type ;
typedef  size_t index_type ;
typedef  scalar_t__ char_type ;
struct TYPE_4__ {int xnum; int ynum; size_t* line_map; int /*<<< orphan*/ * line_attrs; int /*<<< orphan*/ * gpu_cell_buf; int /*<<< orphan*/ * cpu_cell_buf; } ;
typedef  TYPE_1__ LineBuf ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DIRTY_MASK ; 
 int /*<<< orphan*/  clear_chars_to (TYPE_1__*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
linebuf_clear(LineBuf *self, char_type ch) {
    memset(self->cpu_cell_buf, 0, self->xnum * self->ynum * sizeof(CPUCell));
    memset(self->gpu_cell_buf, 0, self->xnum * self->ynum * sizeof(GPUCell));
    memset(self->line_attrs, 0, self->ynum * sizeof(line_attrs_type));
    for (index_type i = 0; i < self->ynum; i++) self->line_map[i] = i;
    if (ch != 0) {
        for (index_type i = 0; i < self->ynum; i++) {
            clear_chars_to(self, i, ch);
            self->line_attrs[i] = TEXT_DIRTY_MASK;
        }
    }
}