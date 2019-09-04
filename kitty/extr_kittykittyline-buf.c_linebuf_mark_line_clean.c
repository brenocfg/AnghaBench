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
typedef  size_t index_type ;
struct TYPE_3__ {int /*<<< orphan*/ * line_attrs; } ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DIRTY_MASK ; 

void
linebuf_mark_line_clean(LineBuf *self, index_type y) {
    self->line_attrs[y] &= ~TEXT_DIRTY_MASK;
}