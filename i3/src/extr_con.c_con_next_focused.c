#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; struct TYPE_12__* parent; int /*<<< orphan*/  focus_head; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_DOCKAREA ; 
 scalar_t__ CT_FLOATING_CON ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* con_descend_focused (TYPE_1__*) ; 
 scalar_t__ con_is_floating (TYPE_1__*) ; 
 int /*<<< orphan*/  focused ; 
 TYPE_1__* output_get_content (TYPE_1__*) ; 

Con *con_next_focused(Con *con) {
    /* dock clients cannot be focused, so we focus the workspace instead */
    if (con->parent->type == CT_DOCKAREA) {
        DLOG("selecting workspace for dock client\n");
        return con_descend_focused(output_get_content(con->parent->parent));
    }
    if (con_is_floating(con)) {
        con = con->parent;
    }

    /* if 'con' is not the first entry in the focus stack, use the first one as
     * it’s currently focused already */
    Con *next = TAILQ_FIRST(&(con->parent->focus_head));
    if (next != con) {
        DLOG("Using first entry %p\n", next);
    } else {
        /* try to focus the next container on the same level as this one or fall
         * back to its parent */
        if (!(next = TAILQ_NEXT(con, focused))) {
            next = con->parent;
        }
    }

    /* now go down the focus stack as far as
     * possible, excluding the current container */
    while (!TAILQ_EMPTY(&(next->focus_head)) && TAILQ_FIRST(&(next->focus_head)) != con) {
        next = TAILQ_FIRST(&(next->focus_head));
    }

    if (con->type == CT_FLOATING_CON && next != con->parent) {
        next = con_descend_focused(next);
    }

    return next;
}