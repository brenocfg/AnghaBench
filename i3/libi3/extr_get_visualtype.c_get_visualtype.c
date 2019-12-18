#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ visual_id; } ;
typedef  TYPE_1__ xcb_visualtype_t ;
struct TYPE_13__ {TYPE_1__* data; scalar_t__ rem; } ;
typedef  TYPE_2__ xcb_visualtype_iterator_t ;
struct TYPE_14__ {scalar_t__ root_visual; } ;
typedef  TYPE_3__ xcb_screen_t ;
struct TYPE_15__ {int /*<<< orphan*/  data; scalar_t__ rem; } ;
typedef  TYPE_4__ xcb_depth_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  xcb_depth_next (TYPE_4__*) ; 
 TYPE_2__ xcb_depth_visuals_iterator (int /*<<< orphan*/ ) ; 
 TYPE_4__ xcb_screen_allowed_depths_iterator (TYPE_3__*) ; 
 int /*<<< orphan*/  xcb_visualtype_next (TYPE_2__*) ; 

xcb_visualtype_t *get_visualtype(xcb_screen_t *screen) {
    xcb_depth_iterator_t depth_iter;
    for (depth_iter = xcb_screen_allowed_depths_iterator(screen);
         depth_iter.rem;
         xcb_depth_next(&depth_iter)) {
        xcb_visualtype_iterator_t visual_iter;
        for (visual_iter = xcb_depth_visuals_iterator(depth_iter.data);
             visual_iter.rem;
             xcb_visualtype_next(&visual_iter)) {
            if (screen->root_visual == visual_iter.data->visual_id)
                return visual_iter.data;
        }
    }
    return NULL;
}