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
typedef  size_t index_type ;
struct TYPE_4__ {scalar_t__* line_attrs; int /*<<< orphan*/  xnum; int /*<<< orphan*/ * line_map; } ;
typedef  TYPE_1__ LineBuf ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 int /*<<< orphan*/  clear_line_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
linebuf_clear_line(LineBuf *self, index_type y) {
    Line l;
    init_line(self, &l, self->line_map[y]);
    clear_line_(&l, self->xnum);
    self->line_attrs[y] = 0;
}