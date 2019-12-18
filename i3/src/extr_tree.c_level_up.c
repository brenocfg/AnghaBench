#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* parent; } ;
struct TYPE_3__ {scalar_t__ type; TYPE_2__* parent; } ;

/* Variables and functions */
 scalar_t__ CT_CON ; 
 scalar_t__ CT_FLOATING_CON ; 
 scalar_t__ CT_WORKSPACE ; 
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  con_activate (TYPE_2__*) ; 
 TYPE_1__* focused ; 

bool level_up(void) {
    /* Skip over floating containers and go directly to the grandparent
     * (which should always be a workspace) */
    if (focused->parent->type == CT_FLOATING_CON) {
        con_activate(focused->parent->parent);
        return true;
    }

    /* We can focus up to the workspace, but not any higher in the tree */
    if ((focused->parent->type != CT_CON &&
         focused->parent->type != CT_WORKSPACE) ||
        focused->type == CT_WORKSPACE) {
        ELOG("'focus parent': Focus is already on the workspace, cannot go higher than that.\n");
        return false;
    }
    con_activate(focused->parent);
    return true;
}