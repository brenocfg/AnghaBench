#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ type; int /*<<< orphan*/  focus_head; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int _con_move_to_con (TYPE_1__*,TYPE_1__*,int,int,int,int,int) ; 
 TYPE_1__* con_by_mark (char const*) ; 
 TYPE_1__* con_get_workspace (TYPE_1__*) ; 
 scalar_t__ con_has_parent (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ con_is_floating (TYPE_1__*) ; 
 scalar_t__ con_is_leaf (TYPE_1__*) ; 
 scalar_t__ con_is_split (TYPE_1__*) ; 
 int /*<<< orphan*/  con_move_to_workspace (TYPE_1__*,TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  scratchpad_move (TYPE_1__*) ; 
 scalar_t__ workspace_get (char*,int /*<<< orphan*/ *) ; 

bool con_move_to_mark(Con *con, const char *mark) {
    Con *target = con_by_mark(mark);
    if (target == NULL) {
        DLOG("found no container with mark \"%s\"\n", mark);
        return false;
    }

    /* For target containers in the scratchpad, we just send the window to the scratchpad. */
    if (con_get_workspace(target) == workspace_get("__i3_scratch", NULL)) {
        DLOG("target container is in the scratchpad, moving container to scratchpad.\n");
        scratchpad_move(con);
        return true;
    }

    /* For floating target containers, we just send the window to the same workspace. */
    if (con_is_floating(target)) {
        DLOG("target container is floating, moving container to target's workspace.\n");
        con_move_to_workspace(con, con_get_workspace(target), true, false, false);
        return true;
    }

    if (target->type == CT_WORKSPACE && con_is_leaf(target)) {
        DLOG("target container is an empty workspace, simply moving the container there.\n");
        con_move_to_workspace(con, target, true, false, false);
        return true;
    }

    /* For split containers, we use the currently focused container within it.
     * This allows setting marks on, e.g., tabbed containers which will move
     * con to a new tab behind the focused tab. */
    if (con_is_split(target)) {
        DLOG("target is a split container, descending to the currently focused child.\n");
        target = TAILQ_FIRST(&(target->focus_head));
    }

    if (con == target || con_has_parent(target, con)) {
        DLOG("cannot move the container to or inside itself, aborting.\n");
        return false;
    }

    return _con_move_to_con(con, target, false, true, false, false, true);
}