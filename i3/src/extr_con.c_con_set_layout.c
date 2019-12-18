#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ layout_t ;
struct TYPE_15__ {scalar_t__ type; scalar_t__ layout; scalar_t__ last_split_layout; int /*<<< orphan*/  nodes_head; struct TYPE_15__* parent; scalar_t__ workspace_layout; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 scalar_t__ L_DEFAULT ; 
 scalar_t__ L_SPLITH ; 
 scalar_t__ L_SPLITV ; 
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_attach (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  con_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  con_force_split_parents_redraw (TYPE_1__*) ; 
 TYPE_1__* con_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ con_num_children (TYPE_1__*) ; 
 int /*<<< orphan*/  croot ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** get_focus_order (TYPE_1__*) ; 
 int /*<<< orphan*/  set_focus_order (TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  tree_flatten (int /*<<< orphan*/ ) ; 

void con_set_layout(Con *con, layout_t layout) {
    DLOG("con_set_layout(%p, %d), con->type = %d\n",
         con, layout, con->type);

    /* Users can focus workspaces, but not any higher in the hierarchy.
     * Focus on the workspace is a special case, since in every other case, the
     * user means "change the layout of the parent split container". */
    if (con->type != CT_WORKSPACE)
        con = con->parent;

    /* We fill in last_split_layout when switching to a different layout
     * since there are many places in the code that don’t use
     * con_set_layout(). */
    if (con->layout == L_SPLITH || con->layout == L_SPLITV)
        con->last_split_layout = con->layout;

    /* When the container type is CT_WORKSPACE, the user wants to change the
     * whole workspace into stacked/tabbed mode. To do this and still allow
     * intuitive operations (like level-up and then opening a new window), we
     * need to create a new split container. */
    if (con->type == CT_WORKSPACE) {
        if (con_num_children(con) == 0) {
            layout_t ws_layout = (layout == L_STACKED || layout == L_TABBED) ? layout : L_DEFAULT;
            DLOG("Setting workspace_layout to %d\n", ws_layout);
            con->workspace_layout = ws_layout;
            DLOG("Setting layout to %d\n", layout);
            con->layout = layout;
        } else if (layout == L_STACKED || layout == L_TABBED || layout == L_SPLITV || layout == L_SPLITH) {
            DLOG("Creating new split container\n");
            /* 1: create a new split container */
            Con *new = con_new(NULL, NULL);
            new->parent = con;

            /* 2: Set the requested layout on the split container and mark it as
             * split. */
            new->layout = layout;
            new->last_split_layout = con->last_split_layout;

            /* 3: move the existing cons of this workspace below the new con */
            Con **focus_order = get_focus_order(con);

            DLOG("Moving cons\n");
            Con *child;
            while (!TAILQ_EMPTY(&(con->nodes_head))) {
                child = TAILQ_FIRST(&(con->nodes_head));
                con_detach(child);
                con_attach(child, new, true);
            }

            set_focus_order(new, focus_order);
            free(focus_order);

            /* 4: attach the new split container to the workspace */
            DLOG("Attaching new split to ws\n");
            con_attach(new, con, false);

            tree_flatten(croot);
        }
        con_force_split_parents_redraw(con);
        return;
    }

    if (layout == L_DEFAULT) {
        /* Special case: the layout formerly known as "default" (in combination
         * with an orientation). Since we switched to splith/splitv layouts,
         * using the "default" layout (which "only" should happen when using
         * legacy configs) is using the last split layout (either splith or
         * splitv) in order to still do the same thing. */
        con->layout = con->last_split_layout;
        /* In case last_split_layout was not initialized… */
        if (con->layout == L_DEFAULT)
            con->layout = L_SPLITH;
    } else {
        con->layout = layout;
    }
    con_force_split_parents_redraw(con);
}