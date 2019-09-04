#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  index_type ;
struct TYPE_5__ {unsigned int cell_y; int /*<<< orphan*/  cell_x; } ;
struct TYPE_6__ {int /*<<< orphan*/ * screen; } ;
struct TYPE_7__ {TYPE_1__ mouse_pos; TYPE_2__ render_data; } ;
typedef  TYPE_3__ Window ;
typedef  int /*<<< orphan*/  SelectionExtendMode ;
typedef  int /*<<< orphan*/  Screen ;

/* Variables and functions */
 int /*<<< orphan*/  EXTEND_CELL ; 
 int /*<<< orphan*/  EXTEND_LINE ; 
 int /*<<< orphan*/  EXTEND_WORD ; 
 int screen_selection_range_for_line (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int screen_selection_range_for_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_start_selection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_update_selection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static inline void
multi_click(Window *w, unsigned int count) {
    Screen *screen = w->render_data.screen;
    index_type start, end;
    bool found_selection = false;
    SelectionExtendMode mode = EXTEND_CELL;
    unsigned int y1 = w->mouse_pos.cell_y, y2 = w->mouse_pos.cell_y;
    switch(count) {
        case 2:
            found_selection = screen_selection_range_for_word(screen, w->mouse_pos.cell_x, &y1, &y2, &start, &end);
            mode = EXTEND_WORD;
            break;
        case 3:
            found_selection = screen_selection_range_for_line(screen, w->mouse_pos.cell_y, &start, &end);
            mode = EXTEND_LINE;
            break;
        default:
            break;
    }
    if (found_selection) {
        screen_start_selection(screen, start, y1, false, mode);
        screen_update_selection(screen, end, y2, false);
    }
}