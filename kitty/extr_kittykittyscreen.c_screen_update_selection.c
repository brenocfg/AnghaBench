#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* index_type ;
struct TYPE_10__ {int /*<<< orphan*/  continued; } ;
struct TYPE_8__ {scalar_t__ end_x; scalar_t__ end_y; int in_progress; scalar_t__ start_y; scalar_t__ start_x; int extend_mode; int /*<<< orphan*/  end_scrolled_by; } ;
struct TYPE_9__ {TYPE_1__ selection; int /*<<< orphan*/  lines; int /*<<< orphan*/  scrolled_by; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
#define  EXTEND_CELL 130 
#define  EXTEND_LINE 129 
#define  EXTEND_WORD 128 
 int /*<<< orphan*/  call_boss (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int screen_selection_range_for_line (TYPE_2__*,void*,void**,void**) ; 
 int screen_selection_range_for_word (TYPE_2__*,void*,void**,void**,void**,void**) ; 
 int /*<<< orphan*/  set_primary_selection ; 
 TYPE_3__* visual_line_ (TYPE_2__*,void*) ; 

void
screen_update_selection(Screen *self, index_type x, index_type y, bool ended) {
    self->selection.end_x = x; self->selection.end_y = y; self->selection.end_scrolled_by = self->scrolled_by;
    if (ended) self->selection.in_progress = false;
    index_type start, end;
    bool found = false;
    bool extending_leftwards = self->selection.end_y < self->selection.start_y || (self->selection.end_y == self->selection.start_y && self->selection.end_x < self->selection.start_x);
    switch(self->selection.extend_mode) {
        case EXTEND_WORD: {
            index_type y1 = y, y2;
            found = screen_selection_range_for_word(self, x, &y1, &y2, &start, &end);
            if (found) {
                if (extending_leftwards) {
                    self->selection.end_x = start; self->selection.end_y = y1;
                    y1 = self->selection.start_y;
                    found = screen_selection_range_for_word(self, self->selection.start_x, &y1, &y2, &start, &end);
                    if (found) {
                        self->selection.start_x = end; self->selection.start_y = y2;
                    }
                } else {
                    self->selection.end_x = end; self->selection.end_y = y2;
                    y1 = self->selection.start_y;
                    found = screen_selection_range_for_word(self, self->selection.start_x, &y1, &y2, &start, &end);
                    if (found) {
                        self->selection.start_x = start; self->selection.start_y = y1;
                    }

                }
            }
            break;
        }
        case EXTEND_LINE: {
            index_type top_line = extending_leftwards ? self->selection.end_y : self->selection.start_y;
            index_type bottom_line = extending_leftwards ? self->selection.start_y : self->selection.end_y;
            while(top_line > 0 && visual_line_(self, top_line)->continued) top_line--;
            while(bottom_line < self->lines - 1 && visual_line_(self, bottom_line + 1)->continued) bottom_line++;
            found = screen_selection_range_for_line(self, top_line, &start, &end);
            if (found) {
                if (extending_leftwards) {
                    self->selection.end_x = start; self->selection.end_y = top_line;
                } else {
                    self->selection.start_x = start; self->selection.start_y = top_line;
                }
            }
            found = screen_selection_range_for_line(self, bottom_line, &start, &end);
            if (found) {
                if (extending_leftwards) {
                    self->selection.start_x = end; self->selection.start_y = bottom_line;
                } else {
                    self->selection.end_x = end; self->selection.end_y = bottom_line;
                }
            }
            break;
        }
        case EXTEND_CELL:
            break;
    }
    if (!self->selection.in_progress) call_boss(set_primary_selection, NULL);
}