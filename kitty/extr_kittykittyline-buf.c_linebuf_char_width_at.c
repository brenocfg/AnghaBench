#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t index_type ;
struct TYPE_6__ {unsigned int attrs; } ;
struct TYPE_5__ {int /*<<< orphan*/ * line_map; } ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 unsigned int WIDTH_MASK ; 
 TYPE_3__* gpu_lineptr (TYPE_1__*,int /*<<< orphan*/ ) ; 

unsigned int
linebuf_char_width_at(LineBuf *self, index_type x, index_type y) {
    return (gpu_lineptr(self, self->line_map[y])[x].attrs) & WIDTH_MASK;
}