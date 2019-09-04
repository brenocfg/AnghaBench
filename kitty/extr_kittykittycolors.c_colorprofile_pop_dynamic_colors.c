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
struct TYPE_3__ {size_t dynamic_color_stack_idx; int /*<<< orphan*/ * dynamic_color_stack; int /*<<< orphan*/  overridden; } ;
typedef  TYPE_1__ ColorProfile ;

/* Variables and functions */

void
colorprofile_pop_dynamic_colors(ColorProfile *self) {
    if (!self->dynamic_color_stack_idx) return;
    self->overridden = self->dynamic_color_stack[--(self->dynamic_color_stack_idx)];
}