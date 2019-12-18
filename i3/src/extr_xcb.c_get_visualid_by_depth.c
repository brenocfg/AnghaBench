#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* data; int /*<<< orphan*/  rem; } ;
typedef  TYPE_2__ xcb_visualtype_iterator_t ;
typedef  int /*<<< orphan*/  xcb_visualid_t ;
struct TYPE_10__ {TYPE_6__* data; scalar_t__ rem; } ;
typedef  TYPE_3__ xcb_depth_iterator_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_11__ {scalar_t__ depth; } ;
struct TYPE_8__ {int /*<<< orphan*/  visual_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  root_screen ; 
 int /*<<< orphan*/  xcb_depth_next (TYPE_3__*) ; 
 TYPE_2__ xcb_depth_visuals_iterator (TYPE_6__*) ; 
 TYPE_3__ xcb_screen_allowed_depths_iterator (int /*<<< orphan*/ ) ; 

xcb_visualid_t get_visualid_by_depth(uint16_t depth) {
    xcb_depth_iterator_t depth_iter;

    depth_iter = xcb_screen_allowed_depths_iterator(root_screen);
    for (; depth_iter.rem; xcb_depth_next(&depth_iter)) {
        if (depth_iter.data->depth != depth)
            continue;

        xcb_visualtype_iterator_t visual_iter;

        visual_iter = xcb_depth_visuals_iterator(depth_iter.data);
        if (!visual_iter.rem)
            continue;
        return visual_iter.data->visual_id;
    }
    return 0;
}