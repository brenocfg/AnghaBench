#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_5__ {scalar_t__ xnum; TYPE_1__* cpu_cells; } ;
struct TYPE_4__ {scalar_t__ ch; } ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 scalar_t__ BLANK_CHAR ; 

unsigned int
line_length(Line *self) {
    index_type last = self->xnum - 1;
    for (index_type i = 0; i < self->xnum; i++) {
        if ((self->cpu_cells[last - i].ch) != BLANK_CHAR) return self->xnum - i;
    }
    return 0;
}