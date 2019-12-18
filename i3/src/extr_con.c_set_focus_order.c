#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  focus_head; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ con_inside_floating (TYPE_1__*) ; 
 int /*<<< orphan*/  focused ; 

void set_focus_order(Con *con, Con **focus_order) {
    int focus_heads = 0;
    while (!TAILQ_EMPTY(&(con->focus_head))) {
        Con *current = TAILQ_FIRST(&(con->focus_head));

        TAILQ_REMOVE(&(con->focus_head), current, focused);
        focus_heads++;
    }

    for (int idx = 0; idx < focus_heads; idx++) {
        /* Useful when encapsulating a workspace. */
        if (con->type != CT_WORKSPACE && con_inside_floating(focus_order[idx])) {
            focus_heads++;
            continue;
        }

        TAILQ_INSERT_TAIL(&(con->focus_head), focus_order[idx], focused);
    }
}