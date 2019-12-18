#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_8__ {scalar_t__ depth; } ;
typedef  TYPE_2__ i3Window ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {scalar_t__ depth; TYPE_1__ frame; } ;
typedef  TYPE_3__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_NONE ; 
 int /*<<< orphan*/  x_con_reframe (TYPE_3__*) ; 

__attribute__((used)) static xcb_window_t _match_depth(i3Window *win, Con *con) {
    xcb_window_t old_frame = XCB_NONE;
    if (con->depth != win->depth) {
        old_frame = con->frame.id;
        con->depth = win->depth;
        x_con_reframe(con);
    }
    return old_frame;
}