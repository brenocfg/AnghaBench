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
struct TYPE_4__ {size_t ynum; int /*<<< orphan*/ * line_attrs; int /*<<< orphan*/  xnum; } ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DIRTY_MASK ; 
 int /*<<< orphan*/  gpu_lineptr (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  set_attribute_on_line (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

void
linebuf_set_attribute(LineBuf *self, unsigned int shift, unsigned int val) {
    for (index_type y = 0; y < self->ynum; y++) {
        set_attribute_on_line(gpu_lineptr(self, y), shift, val, self->xnum);
        self->line_attrs[y] |= TEXT_DIRTY_MASK;
    }
}