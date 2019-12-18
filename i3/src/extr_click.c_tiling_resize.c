#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ event_x; scalar_t__ event_y; int /*<<< orphan*/  event; } ;
typedef  TYPE_3__ xcb_button_press_event_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ click_destination_t ;
struct TYPE_13__ {scalar_t__ height; scalar_t__ y; scalar_t__ width; scalar_t__ x; } ;
struct TYPE_12__ {scalar_t__ height; } ;
struct TYPE_16__ {TYPE_2__ window_rect; TYPE_1__ rect; } ;
struct TYPE_15__ {scalar_t__ height; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_4__ Rect ;
typedef  TYPE_5__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  BORDER_BOTTOM ; 
 int /*<<< orphan*/  BORDER_LEFT ; 
 int /*<<< orphan*/  BORDER_RIGHT ; 
 int /*<<< orphan*/  BORDER_TOP ; 
 scalar_t__ const CLICK_DECORATION ; 
 int /*<<< orphan*/  DLOG (char*,scalar_t__,...) ; 
 TYPE_4__ con_border_style_rect (TYPE_5__*) ; 
 int tiling_resize_for_border (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 

__attribute__((used)) static bool tiling_resize(Con *con, xcb_button_press_event_t *event, const click_destination_t dest, bool use_threshold) {
    /* check if this was a click on the window border (and on which one) */
    Rect bsr = con_border_style_rect(con);
    DLOG("BORDER x = %d, y = %d for con %p, window 0x%08x\n",
         event->event_x, event->event_y, con, event->event);
    DLOG("checks for right >= %d\n", con->window_rect.x + con->window_rect.width);
    if (dest == CLICK_DECORATION) {
        return tiling_resize_for_border(con, BORDER_TOP, event, use_threshold);
    }

    if (event->event_x >= 0 && event->event_x <= (int32_t)bsr.x &&
        event->event_y >= (int32_t)bsr.y && event->event_y <= (int32_t)(con->rect.height + bsr.height))
        return tiling_resize_for_border(con, BORDER_LEFT, event, false);

    if (event->event_x >= (int32_t)(con->window_rect.x + con->window_rect.width) &&
        event->event_y >= (int32_t)bsr.y && event->event_y <= (int32_t)(con->rect.height + bsr.height))
        return tiling_resize_for_border(con, BORDER_RIGHT, event, false);

    if (event->event_y >= (int32_t)(con->window_rect.y + con->window_rect.height))
        return tiling_resize_for_border(con, BORDER_BOTTOM, event, false);

    return false;
}