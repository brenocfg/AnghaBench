#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rectangle_select; } ;
struct TYPE_6__ {int selection_updated_once; int /*<<< orphan*/  last_rendered_url_end; int /*<<< orphan*/  last_rendered_url_start; TYPE_1__ selection; int /*<<< orphan*/  last_rendered_selection_end; int /*<<< orphan*/  last_rendered_selection_start; int /*<<< orphan*/  scrolled_by; int /*<<< orphan*/  last_selection_scrolled_by; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  apply_selection (TYPE_2__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  selection ; 
 int /*<<< orphan*/  selection_limits_ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  url_range ; 

void
screen_apply_selection(Screen *self, void *address, size_t size) {
    memset(address, 0, size);
    self->last_selection_scrolled_by = self->scrolled_by;
    self->selection_updated_once = true;
    selection_limits_(selection, &self->last_rendered_selection_start, &self->last_rendered_selection_end);
    apply_selection(self, address, &self->last_rendered_selection_start, &self->last_rendered_selection_end, 1, self->selection.rectangle_select);
    selection_limits_(url_range, &self->last_rendered_url_start, &self->last_rendered_url_end);
    apply_selection(self, address, &self->last_rendered_url_start, &self->last_rendered_url_end, 2, false);
}