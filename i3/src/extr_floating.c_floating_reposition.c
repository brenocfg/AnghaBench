#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ scratchpad_state; int /*<<< orphan*/  rect; } ;
typedef  int /*<<< orphan*/  Rect ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*) ; 
 scalar_t__ SCRATCHPAD_CHANGED ; 
 scalar_t__ SCRATCHPAD_FRESH ; 
 int floating_maybe_reassign_ws (TYPE_1__*) ; 
 int /*<<< orphan*/  output_containing_rect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_render () ; 

bool floating_reposition(Con *con, Rect newrect) {
    /* Sanity check: Are the new coordinates on any output? If not, we
     * ignore that request. */
    if (!output_containing_rect(newrect)) {
        ELOG("No output found at destination coordinates. Not repositioning.\n");
        return false;
    }

    con->rect = newrect;

    bool reassigned = floating_maybe_reassign_ws(con);

    /* If this is a scratchpad window, don't auto center it from now on. */
    if (con->scratchpad_state == SCRATCHPAD_FRESH)
        con->scratchpad_state = SCRATCHPAD_CHANGED;

    /* Workspace change will already result in a tree_render. */
    if (!reassigned) {
        tree_render();
    }
    return true;
}