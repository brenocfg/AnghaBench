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
typedef  int /*<<< orphan*/  color_type ;
struct TYPE_3__ {int dirty; int /*<<< orphan*/ * color_table; } ;
typedef  TYPE_1__ ColorProfile ;

/* Variables and functions */
 size_t MAX (int,size_t) ; 

void
copy_color_table_to_buffer(ColorProfile *self, color_type *buf, int offset, size_t stride) {
    size_t i;
    stride = MAX(1, stride);
    for (i = 0, buf = buf + offset; i < sizeof(self->color_table)/sizeof(self->color_table[0]); i++, buf += stride) {
        *buf = self->color_table[i];
    }
    self->dirty = false;
}