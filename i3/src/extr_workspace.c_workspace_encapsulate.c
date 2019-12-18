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
struct TYPE_17__ {int /*<<< orphan*/  nodes_head; int /*<<< orphan*/  name; int /*<<< orphan*/  layout; struct TYPE_17__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ELOG (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_attach (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  con_detach (TYPE_1__*) ; 
 TYPE_1__* con_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** get_focus_order (TYPE_1__*) ; 
 int /*<<< orphan*/  set_focus_order (TYPE_1__*,TYPE_1__**) ; 

Con *workspace_encapsulate(Con *ws) {
    if (TAILQ_EMPTY(&(ws->nodes_head))) {
        ELOG("Workspace %p / %s has no children to encapsulate\n", ws, ws->name);
        return NULL;
    }

    Con *new = con_new(NULL, NULL);
    new->parent = ws;
    new->layout = ws->layout;

    Con **focus_order = get_focus_order(ws);

    DLOG("Moving children of workspace %p / %s into container %p\n",
         ws, ws->name, new);
    Con *child;
    while (!TAILQ_EMPTY(&(ws->nodes_head))) {
        child = TAILQ_FIRST(&(ws->nodes_head));
        con_detach(child);
        con_attach(child, new, true);
    }

    set_focus_order(new, focus_order);
    free(focus_order);

    con_attach(new, ws, true);

    return new;
}