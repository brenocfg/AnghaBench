#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i3Window ;
struct TYPE_11__ {scalar_t__ type; int /*<<< orphan*/  layout; struct TYPE_11__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_DOCKAREA ; 
 scalar_t__ CT_FLOATING_CON ; 
 scalar_t__ CT_OUTPUT ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  L_SPLITH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* con_descend_tiling_focused (TYPE_1__*) ; 
 int /*<<< orphan*/  con_fix_percent (TYPE_1__*) ; 
 TYPE_1__* con_new (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* focused ; 

Con *tree_open_con(Con *con, i3Window *window) {
    if (con == NULL) {
        /* every focusable Con has a parent (outputs have parent root) */
        con = focused->parent;
        /* If the parent is an output, we are on a workspace. In this case,
         * the new container needs to be opened as a leaf of the workspace. */
        if (con->parent->type == CT_OUTPUT && con->type != CT_DOCKAREA) {
            con = focused;
        }

        /* If the currently focused container is a floating container, we
         * attach the new container to the currently focused spot in its
         * workspace. */
        if (con->type == CT_FLOATING_CON) {
            con = con_descend_tiling_focused(con->parent);
            if (con->type != CT_WORKSPACE)
                con = con->parent;
        }
        DLOG("con = %p\n", con);
    }

    assert(con != NULL);

    /* 3. create the container and attach it to its parent */
    Con *new = con_new(con, window);
    new->layout = L_SPLITH;

    /* 4: re-calculate child->percent for each child */
    con_fix_percent(con);

    return new;
}