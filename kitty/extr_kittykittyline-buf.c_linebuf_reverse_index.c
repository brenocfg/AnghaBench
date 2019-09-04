#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line_attrs_type ;
typedef  int index_type ;
struct TYPE_3__ {int ynum; int* line_map; int /*<<< orphan*/ * line_attrs; } ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */

void
linebuf_reverse_index(LineBuf *self, index_type top, index_type bottom) {
    if (top >= self->ynum - 1 || bottom >= self->ynum || bottom <= top) return;
    index_type old_bottom = self->line_map[bottom];
    line_attrs_type old_attrs = self->line_attrs[bottom];
    for (index_type i = bottom; i > top; i--) {
        self->line_map[i] = self->line_map[i - 1];
        self->line_attrs[i] = self->line_attrs[i - 1];
    }
    self->line_map[top] = old_bottom;
    self->line_attrs[top] = old_attrs;
}