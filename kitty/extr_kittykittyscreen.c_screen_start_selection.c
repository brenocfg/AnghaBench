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
typedef  void* index_type ;
struct TYPE_4__ {int in_progress; int rectangle_select; int /*<<< orphan*/  extend_mode; int /*<<< orphan*/  end_scrolled_by; int /*<<< orphan*/  start_scrolled_by; void* end_y; void* start_y; void* end_x; void* start_x; } ;
struct TYPE_5__ {TYPE_1__ selection; int /*<<< orphan*/  scrolled_by; } ;
typedef  int /*<<< orphan*/  SelectionExtendMode ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */

void
screen_start_selection(Screen *self, index_type x, index_type y, bool rectangle_select, SelectionExtendMode extend_mode) {
#define A(attr, val) self->selection.attr = val;
    A(start_x, x); A(end_x, x); A(start_y, y); A(end_y, y); A(start_scrolled_by, self->scrolled_by); A(end_scrolled_by, self->scrolled_by);
    A(in_progress, true); A(rectangle_select, rectangle_select); A(extend_mode, extend_mode);
#undef A
}