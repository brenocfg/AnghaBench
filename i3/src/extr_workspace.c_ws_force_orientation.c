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
typedef  scalar_t__ orientation_t ;
struct TYPE_16__ {struct TYPE_16__* layout; int /*<<< orphan*/  nodes_head; struct TYPE_16__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 scalar_t__ HORIZ ; 
 TYPE_1__* L_SPLITH ; 
 TYPE_1__* L_SPLITV ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_attach (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  con_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  con_fix_percent (TYPE_1__*) ; 
 TYPE_1__* con_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** get_focus_order (TYPE_1__*) ; 
 int /*<<< orphan*/  set_focus_order (TYPE_1__*,TYPE_1__**) ; 

void ws_force_orientation(Con *ws, orientation_t orientation) {
    /* 1: create a new split container */
    Con *split = con_new(NULL, NULL);
    split->parent = ws;

    /* 2: copy layout from workspace */
    split->layout = ws->layout;

    /* 3: move the existing cons of this workspace below the new con */
    Con **focus_order = get_focus_order(ws);

    DLOG("Moving cons\n");
    while (!TAILQ_EMPTY(&(ws->nodes_head))) {
        Con *child = TAILQ_FIRST(&(ws->nodes_head));
        con_detach(child);
        con_attach(child, split, true);
    }

    set_focus_order(split, focus_order);
    free(focus_order);

    /* 4: switch workspace layout */
    ws->layout = (orientation == HORIZ) ? L_SPLITH : L_SPLITV;
    DLOG("split->layout = %d, ws->layout = %d\n", split->layout, ws->layout);

    /* 5: attach the new split container to the workspace */
    DLOG("Attaching new split (%p) to ws (%p)\n", split, ws);
    con_attach(split, ws, false);

    /* 6: fix the percentages */
    con_fix_percent(ws);
}