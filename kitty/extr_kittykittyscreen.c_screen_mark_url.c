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
struct TYPE_4__ {int /*<<< orphan*/  end_scrolled_by; int /*<<< orphan*/  start_scrolled_by; void* end_y; void* start_y; void* end_x; void* start_x; } ;
struct TYPE_5__ {int /*<<< orphan*/  scrolled_by; TYPE_1__ url_range; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */

void
screen_mark_url(Screen *self, index_type start_x, index_type start_y, index_type end_x, index_type end_y) {
#define A(attr, val) self->url_range.attr = val;
    A(start_x, start_x); A(end_x, end_x); A(start_y, start_y); A(end_y, end_y); A(start_scrolled_by, self->scrolled_by); A(end_scrolled_by, self->scrolled_by);
#undef A
}