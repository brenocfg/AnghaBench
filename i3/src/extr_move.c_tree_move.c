#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  position_t ;
typedef  scalar_t__ orientation_t ;
typedef  int /*<<< orphan*/  direction_t ;
struct TYPE_29__ {scalar_t__ type; scalar_t__ fullscreen_mode; scalar_t__ layout; int /*<<< orphan*/  deco_render_params; struct TYPE_29__* parent; int /*<<< orphan*/  nodes_head; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  AFTER ; 
 int /*<<< orphan*/  BEFORE ; 
 scalar_t__ CF_GLOBAL ; 
 scalar_t__ CF_OUTPUT ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  D_LEFT ; 
 int /*<<< orphan*/  D_UP ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 scalar_t__ L_DEFAULT ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_PREV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_SWAP (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_to_workspace (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* con_descend_direction (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_fullscreen_permits_focusing (TYPE_1__*) ; 
 TYPE_1__* con_get_workspace (TYPE_1__*) ; 
 scalar_t__ con_inside_floating (TYPE_1__*) ; 
 scalar_t__ con_is_floating (TYPE_1__*) ; 
 int /*<<< orphan*/  con_is_leaf (TYPE_1__*) ; 
 int con_num_children (TYPE_1__*) ; 
 scalar_t__ con_orientation (TYPE_1__*) ; 
 TYPE_1__* con_parent_with_orientation (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  croot ; 
 int /*<<< orphan*/  ewmh_update_wm_desktop () ; 
 int /*<<< orphan*/  floating_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  insert_con_into (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_send_window_event (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  move_to_output_directed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes ; 
 int /*<<< orphan*/  nodes_head ; 
 scalar_t__ orientation_from_direction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_flatten (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_force_orientation (TYPE_1__*,scalar_t__) ; 

void tree_move(Con *con, direction_t direction) {
    position_t position;
    Con *target;

    DLOG("Moving in direction %d\n", direction);

    /* 1: get the first parent with the same orientation */

    if (con->type == CT_WORKSPACE) {
        DLOG("Not moving workspace\n");
        return;
    }

    if (con->fullscreen_mode == CF_GLOBAL) {
        DLOG("Not moving fullscreen global container\n");
        return;
    }

    if ((con->fullscreen_mode == CF_OUTPUT) ||
        (con->parent->type == CT_WORKSPACE && con_num_children(con->parent) == 1)) {
        /* This is the only con on this workspace */
        move_to_output_directed(con, direction);
        return;
    }

    orientation_t o = orientation_from_direction(direction);

    Con *same_orientation = con_parent_with_orientation(con, o);
    /* The do {} while is used to 'restart' at this point with a different
     * same_orientation, see the very last lines before the end of this block
     * */
    do {
        /* There is no parent container with the same orientation */
        if (!same_orientation) {
            if (con_is_floating(con)) {
                /* this is a floating con, we just disable floating */
                floating_disable(con);
                return;
            }
            if (con_inside_floating(con)) {
                /* 'con' should be moved out of a floating container */
                DLOG("Inside floating, moving to workspace\n");
                attach_to_workspace(con, con_get_workspace(con), direction);
                goto end;
            }
            DLOG("Force-changing orientation\n");
            ws_force_orientation(con_get_workspace(con), o);
            same_orientation = con_parent_with_orientation(con, o);
        }

        /* easy case: the move is within this container */
        if (same_orientation == con->parent) {
            Con *swap = (direction == D_LEFT || direction == D_UP)
                            ? TAILQ_PREV(con, nodes_head, nodes)
                            : TAILQ_NEXT(con, nodes);
            if (swap) {
                if (!con_is_leaf(swap)) {
                    DLOG("Moving into our bordering branch\n");
                    target = con_descend_direction(swap, direction);
                    position = (con_orientation(target->parent) != o ||
                                        direction == D_UP ||
                                        direction == D_LEFT
                                    ? AFTER
                                    : BEFORE);
                    insert_con_into(con, target, position);
                    goto end;
                }

                DLOG("Swapping with sibling.\n");
                if (direction == D_LEFT || direction == D_UP) {
                    TAILQ_SWAP(swap, con, &(swap->parent->nodes_head), nodes);
                } else {
                    TAILQ_SWAP(con, swap, &(swap->parent->nodes_head), nodes);
                }

                ipc_send_window_event("move", con);
                return;
            }

            if (con->parent == con_get_workspace(con)) {
                /* If we couldn't find a place to move it on this workspace, try
                 * to move it to a workspace on a different output */
                move_to_output_directed(con, direction);
                return;
            }

            /* If there was no con with which we could swap the current one,
             * search again, but starting one level higher. */
            same_orientation = con_parent_with_orientation(con->parent, o);
        }
    } while (same_orientation == NULL);

    /* this time, we have to move to another container */
    /* This is the container *above* 'con' (an ancestor of con) which is inside
     * 'same_orientation' */
    Con *above = con;
    while (above->parent != same_orientation)
        above = above->parent;

    /* Enforce the fullscreen focus restrictions. */
    if (!con_fullscreen_permits_focusing(above->parent)) {
        LOG("Cannot move out of fullscreen container\n");
        return;
    }

    DLOG("above = %p\n", above);

    Con *next = (direction == D_UP || direction == D_LEFT ? TAILQ_PREV(above, nodes_head, nodes) : TAILQ_NEXT(above, nodes));

    if (next && !con_is_leaf(next)) {
        DLOG("Moving into the bordering branch of our adjacent container\n");
        target = con_descend_direction(next, direction);
        position = (con_orientation(target->parent) != o ||
                            direction == D_UP ||
                            direction == D_LEFT
                        ? AFTER
                        : BEFORE);
        insert_con_into(con, target, position);
    } else if (!next &&
               con->parent->parent->type == CT_WORKSPACE &&
               con->parent->layout != L_DEFAULT &&
               con_num_children(con->parent) == 1) {
        /* Con is the lone child of a non-default layout container at the edge
         * of the workspace. Treat it as though the workspace is its parent
         * and move it to the next output. */
        DLOG("Grandparent is workspace\n");
        move_to_output_directed(con, direction);
        return;
    } else {
        DLOG("Moving into container above\n");
        position = (direction == D_UP || direction == D_LEFT ? BEFORE : AFTER);
        insert_con_into(con, above, position);
    }

end:
    /* force re-painting the indicators */
    FREE(con->deco_render_params);

    ipc_send_window_event("move", con);
    tree_flatten(croot);
    ewmh_update_wm_desktop();
}