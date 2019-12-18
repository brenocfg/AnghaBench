#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  direction_t ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ fullscreen_mode; int /*<<< orphan*/  floating_head; struct TYPE_16__* parent; int /*<<< orphan*/  rect; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CF_NONE ; 
 scalar_t__ CT_FLOATING_CON ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_activate (TYPE_1__*) ; 
 TYPE_1__* con_descend_focused (TYPE_1__*) ; 
 TYPE_1__* con_descend_tiling_focused (TYPE_1__*) ; 
 TYPE_1__* con_get_workspace (TYPE_1__*) ; 
 int /*<<< orphan*/  floating_head ; 
 int /*<<< orphan*/  floating_windows ; 
 TYPE_1__* get_tree_next (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_show (TYPE_1__*) ; 
 int /*<<< orphan*/  x_set_warp_to (int /*<<< orphan*/ *) ; 

void tree_next(Con *con, direction_t direction) {
    Con *next = get_tree_next(con, direction);
    if (!next) {
        return;
    }
    if (next->type == CT_WORKSPACE) {
        /* Show next workspace and focus appropriate container if possible. */
        /* Use descend_focused first to give higher priority to floating or
         * tiling fullscreen containers. */
        Con *focus = con_descend_focused(next);
        if (focus->fullscreen_mode == CF_NONE) {
            Con *focus_tiling = con_descend_tiling_focused(next);
            /* If descend_tiling returned a workspace then focus is either a
             * floating container or the same workspace. */
            if (focus_tiling != next) {
                focus = focus_tiling;
            }
        }

        workspace_show(next);
        con_activate(focus);
        x_set_warp_to(&(focus->rect));
        return;
    } else if (next->type == CT_FLOATING_CON) {
        /* Raise the floating window on top of other windows preserving relative
         * stack order */
        Con *parent = next->parent;
        while (TAILQ_LAST(&(parent->floating_head), floating_head) != next) {
            Con *last = TAILQ_LAST(&(parent->floating_head), floating_head);
            TAILQ_REMOVE(&(parent->floating_head), last, floating_windows);
            TAILQ_INSERT_HEAD(&(parent->floating_head), last, floating_windows);
        }
    }

    workspace_show(con_get_workspace(next));
    con_activate(con_descend_focused(next));
}