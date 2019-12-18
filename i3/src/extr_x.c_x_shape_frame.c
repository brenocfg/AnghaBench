#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_shape_sk_t ;
typedef  int /*<<< orphan*/  xcb_rectangle_t ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_9__ {TYPE_1__ frame; TYPE_6__* window; scalar_t__ border_width; TYPE_2__ window_rect; } ;
typedef  TYPE_3__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_CLIP_ORDERING_UNSORTED ; 
 int /*<<< orphan*/  XCB_SHAPE_SO_SET ; 
 int /*<<< orphan*/  XCB_SHAPE_SO_UNION ; 
 int /*<<< orphan*/  assert (TYPE_6__*) ; 
 int /*<<< orphan*/  conn ; 
 size_t x_get_border_rectangles (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_shape_combine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_shape_rectangles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void x_shape_frame(Con *con, xcb_shape_sk_t shape_kind) {
    assert(con->window);

    xcb_shape_combine(conn, XCB_SHAPE_SO_SET, shape_kind, shape_kind,
                      con->frame.id,
                      con->window_rect.x + con->border_width,
                      con->window_rect.y + con->border_width,
                      con->window->id);
    xcb_rectangle_t rectangles[4];
    size_t rectangles_count = x_get_border_rectangles(con, rectangles);
    if (rectangles_count) {
        xcb_shape_rectangles(conn, XCB_SHAPE_SO_UNION, shape_kind,
                             XCB_CLIP_ORDERING_UNSORTED, con->frame.id,
                             0, 0, rectangles_count, rectangles);
    }
}