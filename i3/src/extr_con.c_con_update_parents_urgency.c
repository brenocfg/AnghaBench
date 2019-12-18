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
struct TYPE_4__ {scalar_t__ type; int urgent; struct TYPE_4__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_DOCKAREA ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  con_has_urgent_child (TYPE_1__*) ; 

void con_update_parents_urgency(Con *con) {
    Con *parent = con->parent;

    /* Urgency hints should not be set on any container higher up in the
     * hierarchy than the workspace level. Unfortunately, since the content
     * container has type == CT_CON, that’s not easy to verify in the loop
     * below, so we need another condition to catch that case: */
    if (con->type == CT_WORKSPACE)
        return;

    bool new_urgency_value = con->urgent;
    while (parent && parent->type != CT_WORKSPACE && parent->type != CT_DOCKAREA) {
        if (new_urgency_value) {
            parent->urgent = true;
        } else {
            /* We can only reset the urgency when the parent
             * has no other urgent children */
            if (!con_has_urgent_child(parent))
                parent->urgent = false;
        }
        parent = parent->parent;
    }
}