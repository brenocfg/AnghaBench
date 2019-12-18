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
struct TYPE_4__ {scalar_t__ type; scalar_t__ layout; int /*<<< orphan*/  focus_head; struct TYPE_4__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_WORKSPACE ; 
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 

bool con_is_hidden(Con *con) {
    Con *current = con;

    /* ascend to the workspace level and memorize the highest-up container
     * which is stacked or tabbed. */
    while (current != NULL && current->type != CT_WORKSPACE) {
        Con *parent = current->parent;
        if (parent != NULL && (parent->layout == L_TABBED || parent->layout == L_STACKED)) {
            if (TAILQ_FIRST(&(parent->focus_head)) != current)
                return true;
        }

        current = parent;
    }

    return false;
}