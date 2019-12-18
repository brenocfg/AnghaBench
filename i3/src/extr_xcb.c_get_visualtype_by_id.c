#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ visual_id; } ;
typedef  TYPE_1__ xcb_visualtype_t ;
struct TYPE_10__ {TYPE_1__* data; scalar_t__ rem; } ;
typedef  TYPE_2__ xcb_visualtype_iterator_t ;
typedef  scalar_t__ xcb_visualid_t ;
struct TYPE_11__ {int /*<<< orphan*/  data; scalar_t__ rem; } ;
typedef  TYPE_3__ xcb_depth_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  root_screen ; 
 int /*<<< orphan*/  xcb_depth_next (TYPE_3__*) ; 
 TYPE_2__ xcb_depth_visuals_iterator (int /*<<< orphan*/ ) ; 
 TYPE_3__ xcb_screen_allowed_depths_iterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_visualtype_next (TYPE_2__*) ; 

xcb_visualtype_t *get_visualtype_by_id(xcb_visualid_t visual_id) {
    xcb_depth_iterator_t depth_iter;

    depth_iter = xcb_screen_allowed_depths_iterator(root_screen);
    for (; depth_iter.rem; xcb_depth_next(&depth_iter)) {
        xcb_visualtype_iterator_t visual_iter;

        visual_iter = xcb_depth_visuals_iterator(depth_iter.data);
        for (; visual_iter.rem; xcb_visualtype_next(&visual_iter)) {
            if (visual_id == visual_iter.data->visual_id) {
                return visual_iter.data;
            }
        }
    }
    return 0;
}