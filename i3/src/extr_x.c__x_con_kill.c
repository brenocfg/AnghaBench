#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ con_state ;
struct TYPE_13__ {scalar_t__ id; } ;
struct TYPE_12__ {scalar_t__ colormap; TYPE_6__ frame; TYPE_6__ frame_buffer; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  CIRCLEQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XCB_NONE ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  draw_util_surface_free (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ focused_id ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  initial_mapping_head ; 
 int /*<<< orphan*/  initial_mapping_order ; 
 scalar_t__ last_focused ; 
 TYPE_1__* old_state ; 
 int /*<<< orphan*/  old_state_head ; 
 TYPE_1__* state_for_frame (scalar_t__) ; 
 int /*<<< orphan*/  state_head ; 
 int /*<<< orphan*/  xcb_free_colormap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xcb_free_pixmap (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void _x_con_kill(Con *con) {
    con_state *state;

    if (con->colormap != XCB_NONE) {
        xcb_free_colormap(conn, con->colormap);
    }

    draw_util_surface_free(conn, &(con->frame));
    draw_util_surface_free(conn, &(con->frame_buffer));
    xcb_free_pixmap(conn, con->frame_buffer.id);
    con->frame_buffer.id = XCB_NONE;
    state = state_for_frame(con->frame.id);
    CIRCLEQ_REMOVE(&state_head, state, state);
    CIRCLEQ_REMOVE(&old_state_head, state, old_state);
    TAILQ_REMOVE(&initial_mapping_head, state, initial_mapping_order);
    FREE(state->name);
    free(state);

    /* Invalidate focused_id to correctly focus new windows with the same ID */
    if (con->frame.id == focused_id) {
        focused_id = XCB_NONE;
    }
    if (con->frame.id == last_focused) {
        last_focused = XCB_NONE;
    }
}