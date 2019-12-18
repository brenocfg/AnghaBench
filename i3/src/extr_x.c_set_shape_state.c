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
struct con_state {scalar_t__ was_floating; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_1__* window; TYPE_2__ frame; } ;
struct TYPE_9__ {scalar_t__ input_shaped; scalar_t__ shaped; } ;
typedef  TYPE_3__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  XCB_SHAPE_SK_BOUNDING ; 
 int /*<<< orphan*/  XCB_SHAPE_SK_INPUT ; 
 scalar_t__ con_is_floating (TYPE_3__*) ; 
 int /*<<< orphan*/  shape_supported ; 
 struct con_state* state_for_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x_shape_frame (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x_unshape_frame (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_shape_state(Con *con, bool need_reshape) {
    if (!shape_supported || con->window == NULL) {
        return;
    }

    struct con_state *state;
    if ((state = state_for_frame(con->frame.id)) == NULL) {
        ELOG("window state for con %p not found\n", con);
        return;
    }

    if (need_reshape && con_is_floating(con)) {
        /* We need to reshape the window frame only if it already has shape. */
        if (con->window->shaped) {
            x_shape_frame(con, XCB_SHAPE_SK_BOUNDING);
        }
        if (con->window->input_shaped) {
            x_shape_frame(con, XCB_SHAPE_SK_INPUT);
        }
    }

    if (state->was_floating && !con_is_floating(con)) {
        /* Remove the shape when container is no longer floating. */
        if (con->window->shaped) {
            x_unshape_frame(con, XCB_SHAPE_SK_BOUNDING);
        }
        if (con->window->input_shaped) {
            x_unshape_frame(con, XCB_SHAPE_SK_INPUT);
        }
    }
}