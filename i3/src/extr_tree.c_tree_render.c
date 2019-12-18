#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 TYPE_1__* croot ; 
 int /*<<< orphan*/  mark_unmapped (TYPE_1__*) ; 
 int /*<<< orphan*/  render_con (TYPE_1__*,int) ; 
 int /*<<< orphan*/  x_push_changes (TYPE_1__*) ; 

void tree_render(void) {
    if (croot == NULL)
        return;

    DLOG("-- BEGIN RENDERING --\n");
    /* Reset map state for all nodes in tree */
    /* TODO: a nicer method to walk all nodes would be good, maybe? */
    mark_unmapped(croot);
    croot->mapped = true;

    render_con(croot, false);

    x_push_changes(croot);
    DLOG("-- END RENDERING --\n");
}