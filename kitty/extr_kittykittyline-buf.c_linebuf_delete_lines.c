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
typedef  scalar_t__ index_type ;
struct TYPE_4__ {scalar_t__ ynum; scalar_t__* line_attrs; int /*<<< orphan*/  xnum; int /*<<< orphan*/ * line_map; int /*<<< orphan*/ * scratch; } ;
typedef  TYPE_1__ LineBuf ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 scalar_t__ CONTINUED_MASK ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  clear_line_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
linebuf_delete_lines(LineBuf *self, index_type num, index_type y, index_type bottom) {
    index_type i;
    index_type ylimit = bottom + 1;
    num = MIN(bottom + 1 - y, num);
    if (y >= self->ynum || y > bottom || bottom >= self->ynum || num < 1) return;
    for (i = y; i < y + num; i++) {
        self->scratch[i] = self->line_map[i];
    }
    for (i = y; i < ylimit && i + num < self->ynum; i++) {
        self->line_map[i] = self->line_map[i + num];
        self->line_attrs[i] = self->line_attrs[i + num];
    }
    self->line_attrs[y] &= ~CONTINUED_MASK;
    for (i = 0; i < num; i++) {
        self->line_map[ylimit - num + i] = self->scratch[y + i];
    }
    Line l;
    for (i = ylimit - num; i < ylimit; i++) {
        init_line(self, &l, self->line_map[i]);
        clear_line_(&l, self->xnum);
        self->line_attrs[i] = 0;
    }
}