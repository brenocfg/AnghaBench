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
typedef  int xcb_shape_sk_t ;
struct con_state {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_2__* window; TYPE_1__ frame; } ;
struct TYPE_10__ {int shaped; int input_shaped; } ;
typedef  TYPE_3__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,TYPE_3__*) ; 
#define  XCB_SHAPE_SK_BOUNDING 129 
#define  XCB_SHAPE_SK_INPUT 128 
 scalar_t__ con_is_floating (TYPE_3__*) ; 
 int /*<<< orphan*/  conn ; 
 struct con_state* state_for_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x_shape_frame (TYPE_3__*,int) ; 
 int /*<<< orphan*/  x_unshape_frame (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

void x_set_shape(Con *con, xcb_shape_sk_t kind, bool enable) {
    struct con_state *state;
    if ((state = state_for_frame(con->frame.id)) == NULL) {
        ELOG("window state for con %p not found\n", con);
        return;
    }

    switch (kind) {
        case XCB_SHAPE_SK_BOUNDING:
            con->window->shaped = enable;
            break;
        case XCB_SHAPE_SK_INPUT:
            con->window->input_shaped = enable;
            break;
        default:
            ELOG("Received unknown shape event kind for con %p. This is a bug.\n",
                 con);
            return;
    }

    if (con_is_floating(con)) {
        if (enable) {
            x_shape_frame(con, kind);
        } else {
            x_unshape_frame(con, kind);
        }

        xcb_flush(conn);
    }
}