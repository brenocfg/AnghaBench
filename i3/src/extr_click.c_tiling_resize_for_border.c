#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_button_press_event_t ;
typedef  int /*<<< orphan*/  orientation_t ;
typedef  scalar_t__ direction_t ;
typedef  int border_t ;
struct TYPE_7__ {scalar_t__ parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
#define  BORDER_BOTTOM 131 
#define  BORDER_LEFT 130 
#define  BORDER_RIGHT 129 
#define  BORDER_TOP 128 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 scalar_t__ D_DOWN ; 
 scalar_t__ D_LEFT ; 
 scalar_t__ D_RIGHT ; 
 scalar_t__ D_UP ; 
 int /*<<< orphan*/  HORIZ ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  VERT ; 
 int /*<<< orphan*/  assert (int) ; 
 int resize_find_tiling_participants (TYPE_1__**,TYPE_1__**,scalar_t__,int) ; 
 int /*<<< orphan*/  resize_graphical_handler (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tree_render () ; 

__attribute__((used)) static bool tiling_resize_for_border(Con *con, border_t border, xcb_button_press_event_t *event, bool use_threshold) {
    DLOG("border = %d, con = %p\n", border, con);
    Con *second = NULL;
    Con *first = con;
    direction_t search_direction;
    switch (border) {
        case BORDER_LEFT:
            search_direction = D_LEFT;
            break;
        case BORDER_RIGHT:
            search_direction = D_RIGHT;
            break;
        case BORDER_TOP:
            search_direction = D_UP;
            break;
        case BORDER_BOTTOM:
            search_direction = D_DOWN;
            break;
    }

    bool res = resize_find_tiling_participants(&first, &second, search_direction, false);
    if (!res) {
        LOG("No second container in this direction found.\n");
        return false;
    }

    assert(first != second);
    assert(first->parent == second->parent);

    /* The first container should always be in front of the second container */
    if (search_direction == D_UP || search_direction == D_LEFT) {
        Con *tmp = first;
        first = second;
        second = tmp;
    }

    const orientation_t orientation = ((border == BORDER_LEFT || border == BORDER_RIGHT) ? HORIZ : VERT);

    resize_graphical_handler(first, second, orientation, event, use_threshold);

    DLOG("After resize handler, rendering\n");
    tree_render();
    return true;
}