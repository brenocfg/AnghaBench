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
typedef  unsigned int index_type ;
struct TYPE_4__ {unsigned int ynum; scalar_t__* line_attrs; int /*<<< orphan*/  xnum; int /*<<< orphan*/ * line_map; int /*<<< orphan*/ * scratch; } ;
typedef  TYPE_1__ LineBuf ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 scalar_t__ CONTINUED_MASK ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  clear_line_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
linebuf_insert_lines(LineBuf *self, unsigned int num, unsigned int y, unsigned int bottom) {
    index_type i;
    if (y >= self->ynum || y > bottom || bottom >= self->ynum) return;
    index_type ylimit = bottom + 1;
    num = MIN(ylimit - y, num);
    if (num > 0) {
        for (i = ylimit - num; i < ylimit; i++) {
            self->scratch[i] = self->line_map[i];
        }
        for (i = ylimit - 1; i >= y + num; i--) {
            self->line_map[i] = self->line_map[i - num];
            self->line_attrs[i] = self->line_attrs[i - num];
        }
        if (y + num < self->ynum) self->line_attrs[y + num] &= ~CONTINUED_MASK;
        for (i = 0; i < num; i++) {
            self->line_map[y + i] = self->scratch[ylimit - num + i];
        }
        Line l;
        for (i = y; i < y + num; i++) {
            init_line(self, &l, self->line_map[i]);
            clear_line_(&l, self->xnum);
            self->line_attrs[i] = 0;
        }
    }
}