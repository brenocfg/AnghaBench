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
struct TYPE_3__ {scalar_t__ dynamic_color_stack_idx; int /*<<< orphan*/  overridden; int /*<<< orphan*/ * dynamic_color_stack; } ;
typedef  TYPE_1__ ColorProfile ;

/* Variables and functions */
 scalar_t__ arraysz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
colorprofile_push_dynamic_colors(ColorProfile *self) {
    if (self->dynamic_color_stack_idx >= arraysz(self->dynamic_color_stack)) {
        memmove(self->dynamic_color_stack, self->dynamic_color_stack + 1, sizeof(self->dynamic_color_stack) - sizeof(self->dynamic_color_stack[0]));
        self->dynamic_color_stack_idx = arraysz(self->dynamic_color_stack) - 1;
    }
    self->dynamic_color_stack[self->dynamic_color_stack_idx++] = self->overridden;
}