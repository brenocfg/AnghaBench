#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ position_t ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 scalar_t__ BEFORE ; 
 int /*<<< orphan*/ * TAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TAILQ_PREV (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ con_fullscreen_permits_focusing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodes ; 
 int /*<<< orphan*/  nodes_head ; 

Con *get_tree_next_sibling(Con *con, position_t direction) {
    Con *to_focus = (direction == BEFORE ? TAILQ_PREV(con, nodes_head, nodes)
                                         : TAILQ_NEXT(con, nodes));
    if (to_focus && con_fullscreen_permits_focusing(to_focus)) {
        return to_focus;
    }
    return NULL;
}