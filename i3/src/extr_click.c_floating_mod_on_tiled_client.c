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
struct TYPE_9__ {int event_x; int event_y; } ;
typedef  TYPE_2__ xcb_button_press_event_t ;
struct TYPE_8__ {int width; int height; } ;
struct TYPE_10__ {TYPE_1__ rect; } ;
typedef  TYPE_3__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  BORDER_BOTTOM ; 
 int /*<<< orphan*/  BORDER_LEFT ; 
 int /*<<< orphan*/  BORDER_RIGHT ; 
 int /*<<< orphan*/  BORDER_TOP ; 
 int /*<<< orphan*/  DLOG (char*,int,int,int,int) ; 
 int tiling_resize_for_border (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static bool floating_mod_on_tiled_client(Con *con, xcb_button_press_event_t *event) {
    /* The client is in tiling layout. We can still initiate a resize with the
     * right mouse button, by chosing the border which is the most near one to
     * the position of the mouse pointer */
    int to_right = con->rect.width - event->event_x,
        to_left = event->event_x,
        to_top = event->event_y,
        to_bottom = con->rect.height - event->event_y;

    DLOG("click was %d px to the right, %d px to the left, %d px to top, %d px to bottom\n",
         to_right, to_left, to_top, to_bottom);

    if (to_right < to_left &&
        to_right < to_top &&
        to_right < to_bottom)
        return tiling_resize_for_border(con, BORDER_RIGHT, event, false);

    if (to_left < to_right &&
        to_left < to_top &&
        to_left < to_bottom)
        return tiling_resize_for_border(con, BORDER_LEFT, event, false);

    if (to_top < to_right &&
        to_top < to_left &&
        to_top < to_bottom)
        return tiling_resize_for_border(con, BORDER_TOP, event, false);

    if (to_bottom < to_right &&
        to_bottom < to_left &&
        to_bottom < to_top)
        return tiling_resize_for_border(con, BORDER_BOTTOM, event, false);

    return false;
}